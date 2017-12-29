#include "button_group.h"
#include "button.h"
#include "h_box_layout_mgr.h"
#include "radio_button.h"
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

void bane::ButtonGroup::onAddChild(const Widget& widget) {
  const Button* b = dynamic_cast<const Button*>(&widget);
  if (!b) {
    throw std::runtime_error{"ButtonGroup only supports buttons as children;"
                             " offending widget: " +
                             widget.id()};
  }

  widget.doOnChange([this](Widget* w) {
    BOOST_LOG_TRIVIAL(trace) << "button " << w->id() << " changed";

    // Ensure only a single radio button is enabled at all times.
    // Other types of buttons (e.g. CheckBox) have no influence as they behave
    // independently
    if (dynamic_cast<RadioButton*>(w)) {
      for (Widget& child : children()) {
        RadioButton* rb{dynamic_cast<RadioButton*>(&child)};
        if (rb && rb != w) {
          rb->setSelected(false);
        }
      }
    }
  });
}

int bane::ButtonGroup::preferredWidth() const noexcept {
  return maxPreferredChildWidth();
}

int bane::ButtonGroup::preferredHeight() const noexcept {
  return static_cast<int>(numChildren());
}

void bane::ButtonGroup::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "ButtonGroup::doRender " << relX() << " "
                           << relY();
}
