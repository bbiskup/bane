#ifndef NCURSES_TERM_WINDOW_H
#define NCURSES_TERM_WINDOW_H

#include "term/term_window.h"

namespace bane {


// Terminal implementation based on ncurses library
class NCursesTermWindow : public TermWindow {
public:
  NCursesTermWindow();
  ~NCursesTermWindow() override;

  void waitForKey() const override;
  void showCursor(bool show = true) override;

protected:
  void setUpMouse() override;
};
} // namespace bane

#endif /* NCURSES_TERM_WINDOW_H */
