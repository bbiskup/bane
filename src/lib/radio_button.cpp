#include "radio_button.h"
#include "event.h"

#include <boost/log/trivial.hpp>

namespace {
// 3 for box itself (o), 1 for space
constexpr const int radioButtonPartWidth{4};
} // namespace

bane::RadioButton::RadioButton(Widget* root, std::string label, bool isSelected)
    : Button{root}, label_{std::move(label)}, isSelected_{isSelected} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "RadioButton: on mouse";
    if (e.clickType == bane::mouse::ClickType::release) {
      isSelected_ = !isSelected_;
      doRender();
      change();
    }
  });
}

int bane::RadioButton::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + radioButtonPartWidth);
}

int bane::RadioButton::preferredHeight() const noexcept { return 1; }

void bane::RadioButton::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "RadioButton::doRender " << relX() << " "
                           << relY();
  CharPoint orig{origin()};
  mvaddstr(orig.y, orig.x, isSelected_ ? "(o)" : "( )");
  mvaddstr(orig.y, orig.x + 3, " ");
  mvaddstr(orig.y, orig.x + 4, label_.c_str());
}

void bane::RadioButton::setSelected(bool isSelected) {
  if (isSelected_ != isSelected) {
    isSelected_ = isSelected;
    doRender();
  }
}
