#include "checkbox.h"

#include <boost/log/trivial.hpp>

namespace {
// 1 for box itself, 1 for space
constexpr const int checkBoxPartWidth{2};
} // namespace

bane::CheckBox::CheckBox(Widget* root, std::string label, bool isChecked)
    : Widget{root}, label_{std::move(label)}, isChecked_{isChecked} {
  doOnMouseRelease([this]() {
    BOOST_LOG_TRIVIAL(trace) << "CheckBox: on mouse release";
    isChecked_ = !isChecked_;
    doRender();
  });
}

int bane::CheckBox::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + checkBoxPartWidth);
}

int bane::CheckBox::preferredHeight() const noexcept { return 1; }

void bane::CheckBox::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "Button::doRender" << y() << " " << x();
  CharPoint orig{origin()};
  mvaddstr(orig.y, orig.x, isChecked_ ? "x" : "_");
  mvaddstr(orig.y, orig.x + 1, " ");
  mvaddstr(orig.y, orig.x + 2, label_.c_str());
}
