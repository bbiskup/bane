#include "button.h"
#include "app.h"
#include <boost/log/trivial.hpp>

bane::Button::Button(Widget* root, std::string label) : Widget{root}, label_{std::move(label)} {
}

int bane::Button::preferredWidth() const noexcept {
  BOOST_LOG_TRIVIAL(trace) << "Button::preferredWidth " << label_.size();
  return static_cast<int>(label_.size());
}
int bane::Button::preferredHeight() const noexcept { return 1; }

void bane::Button::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "Button::doRender" << y() << " " << x();
  CharPoint orig{origin()};
  attrset(app_->theme().active().nCursesColorPair());
  mvaddstr(orig.y, orig.x, label_.c_str());
}

