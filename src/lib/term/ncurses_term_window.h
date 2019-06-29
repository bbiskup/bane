#ifndef NCURSES_TERM_WINDOW_H
#define NCURSES_TERM_WINDOW_H

#include "term/term_window.h"
#include "theme.h"

#include <memory>

namespace bane {

// Terminal implementation based on ncurses library
class NCursesTermWindow : public TermWindow {
public:
  NCursesTermWindow(std::unique_ptr<Theme> theme);
  ~NCursesTermWindow() override;

  void clearScreen() override;
  void waitForKey() const override;
  void showCursor(bool show = true) override;

  void move(int x, int y) override;
  void refresh() override;
  void drawString(int x, int y, const TerminalText& text) override;

  TermWindow& operator<<(const std::string& s) override;
  TermWindow& operator<<(const std::wstring& s) override;
  TermWindow& operator<<(char c) override;
  TermWindow& operator<<(wchar_t c) override;
  TermWindow& operator<<(Font fontWeight) override;
  TermWindow& operator<<(const ColorPair& colorPair) override;

  CharPoint screenDimensions() const override;

protected:
  void setUpMouse() override;
};
} // namespace bane

#endif /* NCURSES_TERM_WINDOW_H */
