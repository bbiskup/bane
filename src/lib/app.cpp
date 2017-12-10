#include "app.h"
#include "event.h"
#include "event_handler.h"
#include "widget.h"

#include <boost/log/trivial.hpp>
#include <mutex>
#include <ncurses.h>

bane::App::App(std::string name, std::unique_ptr<Theme> theme)
    : name_{std::move(name)}, theme_{std::move(theme)} {
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
  MEVENT mort;
  while (true) {
    int c = getch();
    // non-blocking read returns -1

    if (c == KEY_MOUSE) {
      getmouse(&mort);
      switch (mort.bstate) {
      case BUTTON1_CLICKED:
        postEvent<MouseEvent>(mort.x, mort.y, bane::mouse::Button::left,
                              bane::mouse::ClickType::single);
        break;
      case BUTTON1_DOUBLE_CLICKED:
        postEvent<MouseEvent>(mort.x, mort.y, bane::mouse::Button::left,
                              bane::mouse::ClickType::double_);
        break;
      default:
        BOOST_LOG_TRIVIAL(trace) << "Unknown mouse action " << c;
        break;
      };
    } else if (c != -1) {

      switch (c) {
      case KEY_RESIZE:
        postEvent<ResizeEvent>();
        break;
      default:
        BOOST_LOG_TRIVIAL(trace) << "Unknown key " << c;
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
