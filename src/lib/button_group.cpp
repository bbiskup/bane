#include "button_group.h"
#include "button.h"
#include "h_box_layout_mgr.h"
#include "v_box_layout_mgr.h"

#include <boost/log/trivial.hpp>

#include <algorithm>
#include <stdexcept>

bane::ButtonGroup::ButtonGroup(Widget* root, std::string label,
                               Orientation orientation)
    : Widget{root}, label_{std::move(label)} {
  switch (orientation) {
  case Orientation::vertical:
    setLayoutMgr<bane::VBoxLayoutMgr>();
    break;
  case Orientation::horizontal:
    setLayoutMgr<bane::HBoxLayoutMgr>();
    break;
  };
}

void bane::ButtonGroup::checkChild(const Widget& widget) const {
  const Button* b = dynamic_cast<const Button*>(&widget);
  if (!b) {
    throw std::runtime_error{"ButtonGroup only supports buttons as children;"
                             " offending widget: " +
                             widget.id()};
  }
}

int bane::ButtonGroup::preferredWidth() const noexcept {
  return maxPreferredChildWidth();
}

int bane::ButtonGroup::preferredHeight() const noexcept {
  return static_cast<int>(numChildren());
}

void bane::ButtonGroup::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "ButtonGroup::doRender " << relX() << " " << relY();
}
