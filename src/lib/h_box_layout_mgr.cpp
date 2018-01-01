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
    BOOST_LOG_TRIVIAL(trace)
        << "HBoxLayoutMgr::layout " << parent_.relX() << ", " << parent_.relY();
    xOffset += widget.width() + padding;
  }
}

int bane::HBoxLayoutMgr::preferredWidth() const noexcept {
  auto& children = parent_.children();
  // Sum of widths of children
  int sumWidths{std::accumulate(
      children.begin(), children.end(), 0,
      [](int s, const Widget& widget) { return s + widget.preferredWidth(); })};
  int sumPaddings =
      children.empty() ? 0 : static_cast<int>(children.size() - 1);
  return sumWidths + sumPaddings;
}

int bane::HBoxLayoutMgr::preferredHeight() const noexcept {
  return parent_.maxPreferredChildHeight();
}
