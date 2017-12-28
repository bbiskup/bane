#include "term_window.h"
#include <boost/log/trivial.hpp>
#include <ncurses.h>
#include <stdexcept>

namespace {
// Timeout for non-blocking read
constexpr const int nCursesTimeOut{10};
} // namespace

bane::TermWindow::TermWindow() {
  initscr();
  clear();
  noecho();
  timeout(nCursesTimeOut);
  curs_set(0); // no blinking cursor
  // init_pair(1, COLOR_BLUE, COLOR_WHITE);

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
  int xOrigin{widget.absX()};
  int yOrigin{widget.absY()};
  BOOST_LOG_TRIVIAL(trace) << "updateClickMap " << w << "x" << h << "+"
                           << xOrigin << "+" << yOrigin;
  Widget* widgetAddr{&widget};

  // Tolerate out-of-screen updates
  // (A widget may be partially outside the viewport)
  if (w >= width_ || h >= height_) {
    return;
  }

  // direct handle for loop
  std::vector<Widget*>* clickMap{clickMap_.get()};

  for (int x{0}; x < w; ++x) {
    for (int y{}; y < h; ++y) {
      clickMap->at(clickMapIndex(xOrigin + x, yOrigin + y)) = widgetAddr;
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
