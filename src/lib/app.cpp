#include "app.h"
#include "event.h"
#include "widget.h"

#include <boost/log/trivial.hpp>
#include <mutex>
#include <ncurses.h>

bane::App::App(std::string name) : name_{std::move(name)} {
  rootPane.setTermWindow(termWindow_);
  rootPane.resize(termWindow_.width(), termWindow_.height());
}

bane::App::~App() {
  BOOST_LOG_TRIVIAL(trace) << "Terminating application " << name_;
}

void bane::App::render() { rootPane.render(); }

/// Run application - start processing events, until explicit termination
void bane::App::run() {
  render();
  MEVENT mort;
  while (true) {
    int c = getch();
    // non-blocking read returns -1

    if (c == KEY_MOUSE) {
      getmouse(&mort);

      BOOST_LOG_TRIVIAL(trace)
          << "Mouse coordinates: (" << mort.x << ", " << mort.y << ")";
      Widget* widget{};
      switch (mort.bstate) {
      case BUTTON1_CLICKED:
        BOOST_LOG_TRIVIAL(trace) << "Received click";
        widget = termWindow_.widgetAt(mort.x, mort.y);
        if (widget) {
          BOOST_LOG_TRIVIAL(trace) << "Widget: " << widget;
        }
        break;
      case BUTTON1_DOUBLE_CLICKED:
        BOOST_LOG_TRIVIAL(trace) << "Received double click";
        break;
      default:
        BOOST_LOG_TRIVIAL(trace) << "Unknown mouse action " << c;
        break;
      };
    } else if (c != -1) {

      switch (c) {
      case KEY_RESIZE:
        /*
      // This requires ncurses to be configured with --enable-sigwinch
      clear();
      addstr("resize!");
      refresh();
      break;*/
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
        event->handle(&rootPane);
        queue_.pop();
        BOOST_LOG_TRIVIAL(trace) << "Got application event";
      }
    }
  }
}
