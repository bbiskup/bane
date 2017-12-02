#include "app.h"

#include <boost/log/trivial.hpp>
#include <ncurses.h>

bane::App::App(std::string name) : name_{std::move(name)} {}

bane::App::~App() {
  BOOST_LOG_TRIVIAL(trace) << "Terminating application " << name_;
}

/// Run application - start processing events, until explicit termination
void bane::App::run() {
  MEVENT mort;
  while (true) {
    int c = getch();

    if (c == KEY_MOUSE) {
      getmouse(&mort);

      BOOST_LOG_TRIVIAL(trace)
          << "Mouse coordinates: (" << mort.x << ", " << mort.y << ")";
      switch (mort.bstate) {
      case BUTTON1_CLICKED:
        BOOST_LOG_TRIVIAL(trace) << "Received click";
        break;
      case BUTTON1_DOUBLE_CLICKED:
        BOOST_LOG_TRIVIAL(trace) << "Received double click";
        break;
      default:
        BOOST_LOG_TRIVIAL(trace) << "Unknown mouse action " << c;
        break;
      };
    } else {

      switch (c) {
        /*case KEY_RESIZE:
          // This requires ncurses to be configured with --enable-sigwinch
          clear();
          addstr("resize!");
          refresh();
          break;*/
      default:
        BOOST_LOG_TRIVIAL(trace) << "Unknown key " << c;
        break;
      }
    }
  }
}
