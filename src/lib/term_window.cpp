#include <ncurses.h>
#include "term_window.h"

bane::TermWindow::TermWindow() {
  initscr();
  noecho();
  refresh();
}

bane::TermWindow::~TermWindow() { endwin(); }

void bane::TermWindow::waitForKey() const{
    getch();
}

