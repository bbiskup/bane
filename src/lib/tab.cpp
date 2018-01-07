#include "tab.h"

#include "pane.h"
#include "term/term_window.h"

#include <boost/log/trivial.hpp>
#include <stdexcept>

bane::Tab::Tab(Widget* root) : Widget{root} {
  setLayoutMgr<bane::VBoxLayoutMgr>();
  tabHandlesPane_->setLayoutMgr<bane::HBoxLayoutMgr>();
  pane2->addChild<bane::Label>(L"Label 1 of pane 2");
}

int bane::Tab::preferredWidth() const noexcept {
  return layoutMgr_->preferredWidth();
}

int bane::Tab::preferredHeight() const noexcept {
  return layoutMgr_->preferredHeight();
}

void bane::Tab::doRender() {}

