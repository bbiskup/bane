#include "label.h"
#include "screen.h"

int main() {
  bane::Screen screen;

  bane::Label label{"my text"};
  label.resize(10, 20);
  label.render();

  /*  while (true) {
      int c = getch();
      switch (c) {
      case '\n':
        return 0;
      case KEY_RESIZE:
        // This requires ncurses to be configured with --enable-sigwinch
        clear();
        addstr("resize!");
        refresh();
        break;
      default:
        addstr("unknown");
        break;
      };
    }*/
  screen.waitForKey();
  return 0;
}
