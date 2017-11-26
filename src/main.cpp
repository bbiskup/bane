#include "label.h"
#include "term_window.h"

int main() {
  bane::TermWindow termWin;

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
  termWin.waitForKey();
  return 0;
}
