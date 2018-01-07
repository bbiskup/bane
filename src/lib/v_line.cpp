#include "v_line.h"
#include "term/term_window.h"

bane::VLine::VLine(Widget* root, wchar_t lineChar)
    : Widget{root}, lineChar_{lineChar} {}

int bane::VLine::preferredWidth() const noexcept { return 1; }

int bane::VLine::preferredHeight() const noexcept {
  // TODO introduce concept of resize policy (expansion)
  return 10;
}

void bane::VLine::doRender() {
  CharPoint orig{origin()};
  for (int i = 0; i < height(); ++i) {
    termWindow_->move(orig.x, orig.y + i);
    *termWindow_ << lineChar_;
  }
}
