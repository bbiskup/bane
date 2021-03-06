#include "ncurses_term_window.h"
#include "env.h"

#include "ncurses_wrapper.h"
#include <boost/log/trivial.hpp>

#include <clocale>

// Ncurses 'attrset' and other macros use legacy definition of NULL
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"

namespace {
// Timeout for non-blocking read
constexpr const int nCursesTimeOut{10};
} // namespace

bane::NCursesTermWindow::NCursesTermWindow(std::unique_ptr<Theme> theme)
    : TermWindow{std::move(theme)} {
  // Prepare unicode output
  setlocale(LC_CTYPE, bane::locale());

  ::initscr();
  clearScreen();
  ::noecho();
  ::timeout(nCursesTimeOut);
  showCursor(false);
  setUpMouse();
  updateSize();
  ::refresh();
}

bane::NCursesTermWindow::~NCursesTermWindow() { ::endwin(); }

void bane::NCursesTermWindow::clearScreen() {
  *this << theme_->normal();
  ::clear();
}

void bane::NCursesTermWindow::waitForKey() const { ::getch(); }

void bane::NCursesTermWindow::setUpMouse() {
  if (NCURSES_MOUSE_VERSION <= 0) {
    throw std::runtime_error{"No mouse available"};
  }

  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
  printf("\033[?1003h\n"); // make term report mouse movement
  keypad(stdscr, TRUE);
  BOOST_LOG_TRIVIAL(trace) << "Mouse set up";
}

void bane::NCursesTermWindow::showCursor(bool show) { ::curs_set(show); }

void bane::NCursesTermWindow::move(int x, int y) {
  BOOST_LOG_TRIVIAL(trace) << "NCursesTermWindow::move x "
                           << " " << x << " y " << y;
  ::move(y, x);
}

void bane::NCursesTermWindow::refresh() { ::refresh(); }

void bane::NCursesTermWindow::drawString(int x, int y,
                                         const TerminalText& text) {
  mvaddstr(y, x, text.c_str());
}

bane::TermWindow& bane::NCursesTermWindow::operator<<(const std::string& s) {
  addstr(s.c_str());
  return *this;
}

bane::TermWindow& bane::NCursesTermWindow::operator<<(const std::wstring& s) {
  // throws boost ... conversion error
  // BOOST_LOG_TRIVIAL(trace) << L"###################### operator<<" << s;
  addwstr(s.c_str());
  return *this;
}

bane::TermWindow& bane::NCursesTermWindow::operator<<(char c) {
  addch(c);
  return *this;
}

bane::TermWindow& bane::NCursesTermWindow::operator<<(wchar_t c) {
  return operator<<(std::wstring{c});
}

bane::TermWindow& bane::NCursesTermWindow::operator<<(Font fontWeight) {
  switch (fontWeight) {
  case Font::normal:
    standend();
    // attrset(A_NORMAL);
    *this << theme_->normal();
    break;
  case Font::bold:
    attron(A_BOLD);
    break;
  case Font::dim:
    attron(A_DIM);
    break;
  case Font::reverse:
    attron(A_REVERSE);
    break;
  case Font::underline:
    attron(A_UNDERLINE);
    break;
  }
  return *this;
}

bane::CharPoint bane::NCursesTermWindow::screenDimensions() const {
  int width;
  int height;
  getmaxyx(stdscr, height, width);
  return {width, height};
}

bane::TermWindow& bane::NCursesTermWindow::
operator<<(const ColorPair& colorPair) {
  attrset(colorPair.nCursesColorPair());
  return *this;
}

#pragma clang diagnostic pop
