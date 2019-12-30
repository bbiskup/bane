#include "checkbox.h"
#include "app.h"
#include "event/mouse_event.h"
#include "term/term_window.h"

#include <algorithm>
#include <boost/log/trivial.hpp>

namespace {
// 3 for box itself ([x]), 1 for space
constexpr const int checkBoxPartWidth{4};
} // namespace

bane::CheckBox::CheckBox(Widget* parent, std::wstring label, bool isChecked)
    : StatefulButton{parent, label, isChecked} {
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
  const std::string checkMark{state_ ? "x" : " "};
  *termWindow_ << Font::dim << "[" << Font::normal << Font::bold << checkMark
               << Font::normal << Font::dim << "]" << Font::normal << " "
               << label_;
}
