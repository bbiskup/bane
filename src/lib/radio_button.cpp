#include "radio_button.h"
#include "event/mouse_event.h"

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
  BOOST_LOG_TRIVIAL(trace) << "#### pick " << this;
  BOOST_LOG_TRIVIAL(trace) << "@1";
  setState();
    BOOST_LOG_TRIVIAL(trace) << "@2";
    render();
    BOOST_LOG_TRIVIAL(trace) << "@3";
    change();
    BOOST_LOG_TRIVIAL(trace) << "@4";
}

int bane::RadioButton::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + radioButtonPartWidth);
}

int bane::RadioButton::preferredHeight() const noexcept { return 1; }

void bane::RadioButton::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "RadioButton::doRender " << relX() << " "
                           << relY();
  CharPoint orig{origin()};
  mvaddstr(orig.y, orig.x, state_ ? "(o)" : "( )");
  mvaddstr(orig.y, orig.x + 3, " ");
  mvaddstr(orig.y, orig.x + 4, label_.c_str());
}
