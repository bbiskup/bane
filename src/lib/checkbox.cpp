#include "checkbox.h"
#include "event.h"

#include <boost/log/trivial.hpp>

namespace {
// 3 for box itself ([x]), 1 for space
constexpr const int checkBoxPartWidth{4};
} // namespace

bane::CheckBox::CheckBox(Widget* root, std::string label, bool isChecked)
    : Button{root}, label_{std::move(label)}, isChecked_{isChecked} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "CheckBox: on mouse";

    if (e.clickType == mouse::ClickType::single || e.clickType == mouse::ClickType::release) {
      isChecked_ = !isChecked_;
      doRender();
      change();
    }
  });
}

int bane::CheckBox::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + checkBoxPartWidth);
}

int bane::CheckBox::preferredHeight() const noexcept { return 1; }

void bane::CheckBox::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "CheckBox::doRender " << relX() << " " << relY();
  CharPoint orig{origin()};
  mvaddstr(orig.y, orig.x, isChecked_ ? "[x]" : "[ ]");
  mvaddstr(orig.y, orig.x + 3, " ");
  mvaddstr(orig.y, orig.x + 4, label_.c_str());
}
