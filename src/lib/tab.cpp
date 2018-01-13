#include "tab.h"
#include "term/term_window.h"

bane::Tab::Tab(Widget* parent, std::wstring label)
    : Widget{parent}, label_{std::move(label)} {}

int bane::Tab::preferredWidth() const noexcept {
  return layoutMgr_->preferredWidth();
}

int bane::Tab::preferredHeight() const noexcept {
  return layoutMgr_->preferredHeight();
}

void bane::Tab::doRender() {
  //*termWindow_ << "Tab::doRender TODO";
}
