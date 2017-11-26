#include "label.h"
#include "term_window.h"
#include "pane.h"
#include "h_box_layout_mgr.h"

int main() {
  bane::TermWindow termWin;

  bane::Pane pane{};
  pane.setLayoutMgr<bane::HBoxLayoutMgr>();
  pane.addChild<bane::Label>("my_text");
  pane.addChild<bane::Label>("my_other_text");
  //bane::Label label{"my text"};
  //label.resize(10, 20);
  //label.render();
  pane.resize(40,50);
  pane.render();

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
