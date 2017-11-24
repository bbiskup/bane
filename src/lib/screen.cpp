#include <ncurses.h>
#include "screen.h"

bane::Screen::Screen() {
  initscr();
  noecho();
  refresh();
}

bane::Screen::~Screen() { endwin(); }

void bane::Screen::waitForKey() const{
    getch();
}

