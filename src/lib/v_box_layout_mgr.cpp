#include "v_box_layout_mgr.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <iostream>

void bane::VBoxLayoutMgr::layout(const Widget& parent,
                                 boost::ptr_vector<Widget>& widgets) {
  const int padding{0};
  int yOffset{0};
  for (Widget& widget : widgets) {
    widget.resizeToPreferred();
    widget.move(parent.x(), parent.y() + yOffset);
    BOOST_LOG_TRIVIAL(trace) << "VBoxLayoutMgr::layout " << parent.x() + yOffset
                             << ", " << parent.y();
    yOffset += widget.height() + padding;
  }
}
