#include "radio_button.h"
#include "event/mouse_event.h"
#include "term/term_window.h"

#include <boost/log/trivial.hpp>

namespace {
// 3 for box itself (o), 1 for space
constexpr const int radioButtonPartWidth{4};
} // namespace

bane::RadioButton::RadioButton(Widget* root, std::string label, bool isSelected)
    : StatefulButton{root, isSelected}, label_{std::move(label)} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "RadioButton: on mouse";
    if (e.clickType == mouse::ClickType::single ||
        e.clickType == mouse::ClickType::release) {
      pick();
    }
  });
}

/// Activate and refresh UI
void bane::RadioButton::pick() {
  setState();
  render();
  change();
}

int bane::RadioButton::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + radioButtonPartWidth);
}

int bane::RadioButton::preferredHeight() const noexcept { return 1; }

void bane::RadioButton::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "RadioButton::doRender " << relX() << " "
                           << relY();
  CharPoint orig{origin()};
  termWindow_->drawString(orig, state_ ? "(o)" : "( )");
  termWindow_->drawString(orig.x + 3, orig.y, " ");
  termWindow_->drawString(orig.x + 4, orig.y, label_);
}
