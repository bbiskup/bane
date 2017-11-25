#include "term_window.h"
#include <ncurses.h>

bane::TermWindow::TermWindow() {
  initscr();
  noecho();
  refresh();
}

bane::TermWindow::~TermWindow() { endwin(); }

void bane::TermWindow::updateSize() {
  getmaxyx(stdscr, height_, width_);
  clickMap_.reset(new std::vector<Widget*>{static_cast<unsigned long>(width_ * height_)});
  // TODO repaint all widgets
}

void bane::TermWindow::waitForKey() const { getch(); }
