#include "push_button.h"
#include "app.h"
#include "event/mouse_event.h"
#include <boost/log/trivial.hpp>

bane::PushButton::PushButton(Widget* parent, std::wstring label)
    : Widget{parent}, label_{std::move(label)} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "PushButton: on mouse";
    if (e.button == mouse::Button::left) {
      switch (e.clickType) {
      case bane::mouse::ClickType::single:
        isPressed_ = true;
        doRender();
        break;
      case bane::mouse::ClickType::release:
        isPressed_ = false;
        doRender();
        break;
      case bane::mouse::ClickType::double_:
        break;
      case bane::mouse::ClickType::none:
      case bane::mouse::ClickType::notImplemented:
        break;
      };
    }
  });
}

int bane::PushButton::preferredWidth() const noexcept {
  BOOST_LOG_TRIVIAL(trace) << "PushButton::preferredWidth " << label_.size();
  return static_cast<int>(label_.size());
}
int bane::PushButton::preferredHeight() const noexcept { return 1; }

void bane::PushButton::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "PushButton::doRender " << relX() << " "
                           << relY();
  //CharPoint orig{origin()};
  if (isPressed_) {
    attrset(app_->theme().engaged().nCursesColorPair());
  } else {
    attrset(app_->theme().active().nCursesColorPair());
  }
  //termWindow_->drawString(orig, label_);
  *termWindow_ << Font::normal << label_ << Font::normal;
  //attrset(app_->theme().normal().nCursesColorPair());
}
