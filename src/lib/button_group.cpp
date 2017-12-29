#include "button_group.h"
#include "app.h"
#include "event/key_event.h"
#include "h_box_layout_mgr.h"
#include "radio_button.h"
#include "stateful_button.h"
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

void bane::ButtonGroup::onAddChild(Widget& widget) {
  StatefulButton* b = dynamic_cast<StatefulButton*>(&widget);
  if (!b) {
    throw std::runtime_error{"ButtonGroup only supports buttons as children;"
                             " offending widget: " +
                             widget.id()};
  }

  widget.doOnKey([this, b](const KeyEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "### doOnKey";
    if (e.specialKey) {
      if (*e.specialKey == SpecialKey::arrowDown) {
        Widget* nextSib = b->nextSibling();
        if (nextSib) {
          nextSib->requestFocus();
        }
      } else if (*e.specialKey == SpecialKey::arrowUp) {
        Widget* prevSib = b->previousSibling();
        if (prevSib) {
          prevSib->requestFocus();
        }
      }
    } else if (e.c == ' ') {
      BOOST_LOG_TRIVIAL(trace) << "#### b: " << this;
      b->pick();
    }
    render();
  });

  widget.doOnChange([this](Widget* w) {
    BOOST_LOG_TRIVIAL(trace) << "button " << w->id() << " changed";

    // Ensure only a single radio button is enabled at all times.
    // Other types of buttons (e.g. CheckBox) have no influence as they behave
    // independently
    if (dynamic_cast<RadioButton*>(w)) {
      for (Widget& child : children()) {
        RadioButton* rb{dynamic_cast<RadioButton*>(&child)};
        if (rb && rb != w) {
          rb->setState(false);
        }
      }
    }
    render();
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
