#include "tabs.h"
#include "tab.h"

#include "pane.h"
#include "term/term_window.h"
#include "label.h"
#include "v_box_layout_mgr.h"
#include "h_box_layout_mgr.h"

#include <boost/log/trivial.hpp>
#include <stdexcept>

bane::Tabs::Tabs(Widget* root) : Widget{root} {
  setLayoutMgr<bane::VBoxLayoutMgr>();
  // Must happen after widget creation
  // TODO: initialization of termWindow_ etc. should happen in
  // Widget ctor, referencing parent widget
  handlesPane_ = addChild<bane::Pane>();
  handlesPane_->setLayoutMgr<bane::HBoxLayoutMgr>();
}

int bane::Tabs::preferredWidth() const noexcept {
  return layoutMgr_->preferredWidth();
}

int bane::Tabs::preferredHeight() const noexcept {
  return layoutMgr_->preferredHeight();
}

void bane::Tabs::doRender() {}

bane::Tab* bane::Tabs::addTab(std::wstring name){
  return handlesPane_->addChild<bane::Tab>(std::move(name));
}

