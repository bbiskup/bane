#include "checkbox.h"
#include "event/mouse_event.h"
#include "term/term_window.h"

#include <boost/log/trivial.hpp>

namespace {
// 3 for box itself ([x]), 1 for space
constexpr const int checkBoxPartWidth{4};
} // namespace

bane::CheckBox::CheckBox(Widget* root, std::string label, bool isChecked)
    : StatefulButton{root, isChecked}, label_{std::move(label)} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "CheckBox: on mouse";

    if (e.clickType == mouse::ClickType::single ||
        e.clickType == mouse::ClickType::release) {
      pick();
    }
  });
}

/// Activate and refresh UI
void bane::CheckBox::pick() {
  toggleState();
  render();
  change();
}

int bane::CheckBox::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + checkBoxPartWidth);
}

int bane::CheckBox::preferredHeight() const noexcept { return 1; }

void bane::CheckBox::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "CheckBox::doRender " << relX() << " " << relY();
  CharPoint orig{origin()};
  termWindow_->drawString(orig, state_ ? "[x]" : "[ ]");
  termWindow_->drawString(orig.x + 3, orig.y, " ");
  termWindow_->drawString(orig.x + 4, orig.y, label_);
}
