#include "v_box_layout_mgr.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <iostream>

void bane::VBoxLayoutMgr::layout() {
  const int padding{0};
  int yOffset{0};
  for (Widget& child : parent_.children()) {
    child.resizeToPreferred();
    child.moveTo(0, yOffset);
    BOOST_LOG_TRIVIAL(trace)
        << "VBoxLayoutMgr::layout " << parent_.id() << " -- " << child.id()
        << " " << child.relX() << ", " << child.relY() << " " << child.width()
        << "x" << child.height();
    yOffset += child.height() + padding;
  }
}

int bane::VBoxLayoutMgr::preferredWidth() const noexcept {
  return parent_.maxPreferredChildWidth();
}

int bane::VBoxLayoutMgr::preferredHeight() const noexcept {
  // Sum of heights of children
  return std::accumulate(
      parent_.children().begin(), parent_.children().end(), 0,
      [](int s, const Widget& widget) { return s + widget.preferredHeight(); });
}
