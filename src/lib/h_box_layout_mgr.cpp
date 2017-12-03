#include "h_box_layout_mgr.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <iostream>

void bane::HBoxLayoutMgr::layout(const Widget& parent,
                                 boost::ptr_vector<Widget>& widgets) {
  const int padding{1};
  int xOffset{0};
  for (Widget& widget : widgets) {
    widget.resizeToPreferred();
    widget.move(parent.x() + xOffset, parent.y());
    BOOST_LOG_TRIVIAL(trace) << "HBoxLayoutMgr::layout " << parent.x() + xOffset
                             << ", " << parent.y();
    xOffset += widget.width() + padding;
  }
}
