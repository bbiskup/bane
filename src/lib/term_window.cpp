#include "term_window.h"
#include <ncurses.h>

bane::TermWindow::TermWindow() {
  initscr();
  noecho();
  refresh();
}

bane::TermWindow::~TermWindow() { endwin(); }

/// Indicate area occupied by Widget
void bane::TermWindow::updateClickMap(Widget& widget) {
  int w{widget.width()};
  int h{widget.height()};
  Widget* widgetAddr{&widget};

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
  clickMap_.reset(
      new std::vector<Widget*>{static_cast<unsigned long>(width_ * height_)});
  // TODO repaint all widgets
}

void bane::TermWindow::waitForKey() const { getch(); }
