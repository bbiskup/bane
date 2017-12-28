#include "v_box_layout_mgr.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <iostream>

void bane::VBoxLayoutMgr::layout() {
  const int padding{0};
  int yOffset{0};
  for (Widget& widget : parent_.children()) {
    widget.resizeToPreferred();
    widget.move(parent_.x(), parent_.y() + yOffset);
    BOOST_LOG_TRIVIAL(trace) << "VBoxLayoutMgr::layout "
                             << parent_.x() + yOffset << ", " << parent_.y();
    yOffset += widget.height() + padding;
  }
}

int bane::VBoxLayoutMgr::preferredWidth() const noexcept {
  return parent_.maxPreferredChildWidth();
}

int bane::VBoxLayoutMgr::preferredHeight() const noexcept {
  return static_cast<int>(parent_.numChildren());
}
