#include "h_box_layout_mgr.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <iostream>

void bane::HBoxLayoutMgr::layout() {
  const int padding{1};
  int xOffset{0};
  for (Widget& widget : parent_.children()) {
    widget.resizeToPreferred();
    widget.moveTo(parent_.relX() + xOffset, parent_.relY());
    BOOST_LOG_TRIVIAL(trace) << "HBoxLayoutMgr::layout "
                             << parent_.relX() << ", " << parent_.relY();
    xOffset += widget.width() + padding;
  }
}

int bane::HBoxLayoutMgr::preferredWidth() const noexcept {
  return parent_.maxPreferredChildWidth();
}

int bane::HBoxLayoutMgr::preferredHeight() const noexcept {
  return parent_.maxPreferredChildHeight();
}
