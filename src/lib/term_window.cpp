#include "term_window.h"
#include <boost/log/trivial.hpp>
#include <ncurses.h>
#include <stdexcept>

namespace {
// Timeout for non-blocking read
constexpr const int nCursesTimeOut{100};
} // namespace

bane::TermWindow::TermWindow() {
  initscr();
  clear();
  noecho();
  timeout(nCursesTimeOut);
  curs_set(0);   // no blinking cursor
  start_color(); // must come before creating windows
  init_pair(1, COLOR_BLUE, COLOR_WHITE);

  setUpMouse();
  updateSize();
  refresh();
}

bane::TermWindow::~TermWindow() { endwin(); }

void bane::TermWindow::setUpMouse() {
  if (NCURSES_MOUSE_VERSION <= 0) {
    throw std::runtime_error{"No mouse available"};
  }

  mousemask(ALL_MOUSE_EVENTS, nullptr);
  keypad(stdscr, TRUE);
  BOOST_LOG_TRIVIAL(trace) << "Mouse set up";
}

/// Indicate area occupied by Widget
void bane::TermWindow::updateClickMap(Widget& widget) {
  int w{widget.width()};
  int h{widget.height()};
  BOOST_LOG_TRIVIAL(trace) << "updateClickMap " << w << ", " << h;
  Widget* widgetAddr{&widget};

  // Tolerate out-of-screen updates
  // (A widget may be partially outside the viewport)
  if (w >= width_ || h >= height_) {
    return;
  }

  // direct handle for loop
  std::vector<Widget*>* clickMap{clickMap_.get()};

  for (int x{0}; x < w; ++x) {
    for (int y{0}; y < h; ++y) {
      clickMap->at(clickMapIndex(x, y)) = widgetAddr;
    }
  }
}

bane::Widget* bane::TermWindow::widgetAt(int x, int y) const {
  return clickMap_->at(clickMapIndex(x, y));
}

void bane::TermWindow::updateSize() {
  getmaxyx(stdscr, height_, width_);
  BOOST_LOG_TRIVIAL(trace) << "updateSize " << width_ << ", " << height_;
  clickMap_.reset(
      new std::vector<Widget*>{static_cast<unsigned long>(width_ * height_)});
  // TODO repaint all widgets
}

void bane::TermWindow::waitForKey() const { getch(); }
