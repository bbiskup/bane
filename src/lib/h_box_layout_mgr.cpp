#include  "h_box_layout_mgr.h"
#include  "widget.h"

void bane::HBoxLayoutMgr::layout(const Widget& parent,
                                 boost::ptr_vector<Widget>& widgets) {
  int xOffset{0};
  for (Widget& widget : widgets) {
      widget.resizeToPreferred();
      widget.move(parent.x() + xOffset, 0);
      xOffset += widget.width();
  }
}
