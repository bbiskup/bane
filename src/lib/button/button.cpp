#include "button.h"
#include "app.h"
#include "event/mouse_event.h"
#include <boost/log/trivial.hpp>

bane::Button::Button(Widget* root, std::string label)
    : Widget{root}, label_{std::move(label)} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "Button: on mouse";
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
      };
    }
  });
}

int bane::Button::preferredWidth() const noexcept {
  BOOST_LOG_TRIVIAL(trace) << "Button::preferredWidth " << label_.size();
  return static_cast<int>(label_.size());
}
int bane::Button::preferredHeight() const noexcept { return 1; }

void bane::Button::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "Button::doRender " << relX() << " " << relY();
  CharPoint orig{origin()};
  if (isPressed_) {
    attrset(app_->theme().engaged().nCursesColorPair());
  } else {
    attrset(app_->theme().active().nCursesColorPair());
  }
  mvaddstr(orig.y, orig.x, label_.c_str());
}
