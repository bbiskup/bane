#include  "h_box_layout_mgr.h"
#include  "widget.h"
#include <iostream>

void bane::HBoxLayoutMgr::layout(const Widget& parent,
                                 boost::ptr_vector<Widget>& widgets) {
  const int padding{1};
  int xOffset{0};
  for (Widget& widget : widgets) {
      widget.resizeToPreferred();
      widget.move(parent.x() + xOffset, parent.y());
      //std::cout << "### " << parent.x() + xOffset << ", " <<  parent.y() << std::endl;
      xOffset += widget.width() + padding;
  }
}
