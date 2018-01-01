#include "h_line.h"
#include "term/term_window.h"

bane::HLine::HLine(Widget* root, char lineChar)
    : Widget{root}, lineChar_{lineChar} {}

int bane::HLine::preferredWidth() const noexcept { 
    // TODO introduce concept of resize policy (expansion)
    return 10; }
int bane::HLine::preferredHeight() const noexcept { return 1; }

void bane::HLine::doRender() {
  std::string line(static_cast<std::string::size_type>(width()), lineChar_);
  *termWindow_ << line;
}
