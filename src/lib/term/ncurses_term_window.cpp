#include "ncurses_term_window.h"

#include <ncurses.h>
#include <boost/log/trivial.hpp>

namespace {
// Timeout for non-blocking read
constexpr const int nCursesTimeOut{10};
} // namespace

bane::NCursesTermWindow::NCursesTermWindow() {
  initscr();
  clear();
  noecho();
  timeout(nCursesTimeOut);
  showCursor(false);
  // init_pair(1, COLOR_BLUE, COLOR_WHITE);

  setUpMouse();
  updateSize();
  refresh();
}

bane::NCursesTermWindow::~NCursesTermWindow() { endwin(); }

void bane::NCursesTermWindow::waitForKey() const { getch(); }

void bane::NCursesTermWindow::setUpMouse() {
  if (NCURSES_MOUSE_VERSION <= 0) {
    throw std::runtime_error{"No mouse available"};
  }

  mousemask(ALL_MOUSE_EVENTS, nullptr);
  keypad(stdscr, TRUE);
  BOOST_LOG_TRIVIAL(trace) << "Mouse set up";
}

void bane::NCursesTermWindow::showCursor(bool show) { curs_set(show); }
