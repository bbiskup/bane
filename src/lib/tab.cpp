#include "tab.h"

#include "term/term_window.h"

bane::Tab::Tab(Widget* root) : Widget{root} {}

int bane::Tab::preferredWidth() const noexcept {
  return layoutMgr_->preferredWidth();
}

int bane::Tab::preferredHeight() const noexcept {
  return layoutMgr_->preferredHeight();
}

void bane::Tab::doRender() {}
