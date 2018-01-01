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

  void move(int x, int y) override;
  void refresh() override;
  void drawString(int x, int y, const TerminalText& text) override;

  TermWindow& operator<<(const std::string s) override;
  TermWindow& operator<<(Font fontWeight) override;

  CharPoint screenDimensions() const override;

protected:
  void setUpMouse() override;
};
} // namespace bane

#endif /* NCURSES_TERM_WINDOW_H */
