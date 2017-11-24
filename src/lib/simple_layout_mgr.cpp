#include "simple_layout_mgr.h"
#include "widget.h"
#include <stdexcept>

void bane::SimpleLayoutMgr::layout(
    const Widget& parent, boost::ptr_vector<Widget>& widgets)  {
  if (widgets.size() == 0) {
    return;
  } else if (widgets.size() > 1) {
    throw std::runtime_error{"Expecting exactly 1 child"};
  } else {
    Widget& w = widgets[0];
    w.move(parent.x(), parent.y());
  }
}
