#include "button.h"
#include "app.h"
#include <boost/log/trivial.hpp>

bane::Button::Button(Widget* root, std::string label)
    : Widget{root}, label_{std::move(label)} {
  doOnClick([this](int, int) {
    BOOST_LOG_TRIVIAL(trace) << "on mouse press";
    isPressed_ = true;
    doRender();
  });
  doOnMouseRelease([this]() {
    BOOST_LOG_TRIVIAL(trace) << "on mouse release";
    isPressed_ = false;
    doRender();
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
