#include "app.h"
#include "event/event.h"
#include "event/event_handler.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/resize_event.h"
#include "widget.h"

#include <boost/log/trivial.hpp>
#include <ncurses.h>

#include <mutex>
#include <utility>

bane::App::App(std::string name, std::unique_ptr<Theme> theme)
    : name_{std::move(name)}, theme_{std::move(theme)} {
  rootPane.setApp(*this);
  rootPane.setTermWindow(termWindow_);
  handleResize();
  rootPane.render();
}

bane::App::~App() {
  BOOST_LOG_TRIVIAL(trace) << "Terminating application " << name_;
}

void bane::App::render() { rootPane.render(); }
void bane::App::handleResize() {
  BOOST_LOG_TRIVIAL(trace) << "App::handleResize";
  termWindow_.updateSize();
  rootPane.resize(termWindow_.width(), termWindow_.height());
  clear();
  refresh();
  rootPane.render();
}

/// Run application - start processing events, until explicit termination
void bane::App::run() {
  EventHandler eventHandler(*this);
  BOOST_LOG_TRIVIAL(trace) << "App::run";
  render();
  while (true) {
    int c = getch();
    // non-blocking read returns -1

    if (c == KEY_MOUSE) {
      dispatchMouseEvent(c);
    } else if (c != -1) {

      switch (c) {
      case KEY_RESIZE:
        postEvent<ResizeEvent>();
        break;
      default:
        dispatchKeyEvent(c);
        break;
      }
    }

    // Check for application events
    std::unique_lock<std::mutex> lock{queueMutex_, std::try_to_lock};
    if (lock.owns_lock()) {
      if (queue_.size()) {
        std::unique_ptr<Event> event = std::move(queue_.front());
        BOOST_LOG_TRIVIAL(trace) << "Got application event " << event->name();
        event->accept(eventHandler);
        queue_.pop();
      }
    }
  }
}

/// Create and post a mouse event, translating from ncurses
/// \param c ncurses character
void bane::App::dispatchMouseEvent(int c) {
  postEvent<MouseEvent>(c);
}

/// Create and post a mouse event, translating from ncurses
/// \param c ncurses character
void bane::App::dispatchKeyEvent(int c) {
  int x, y;
  getyx(stdscr, y, x);
  postEvent<KeyEvent>(x, y, c);
}
