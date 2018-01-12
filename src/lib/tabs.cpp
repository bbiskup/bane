#include "tabs.h"
#include "tab.h"

#include "h_box_layout_mgr.h"
#include "label.h"
#include "pane.h"
#include "term/term_window.h"
#include "v_box_layout_mgr.h"

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

bane::Tab* bane::Tabs::addTab(std::wstring name) {
  Tab* result{handlesPane_->addChild<bane::Tab>(std::move(name))};

  // select latest tab
  selectTab(numTabs() - 1);

  return result;
}

/// Select (show) tab at given index
void bane::Tabs::selectTab(size_t tabIndex) {
  size_t nTabs{numTabs()};
  if (tabIndex >= nTabs) {
    throw std::out_of_range{"Tab index" + std::to_string(tabIndex)
                                        + " out of range"};
  }

  for (size_t i{0}; i < nTabs; ++i) {
    handlesPane_->children().at(i).visible(i == tabIndex);
  }
}
