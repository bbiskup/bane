#include "button.h"
#include "term_window.h"

#include <boost/log/trivial.hpp>

void bane::Button::onFocus() {
  BOOST_LOG_TRIVIAL(trace) << "Button::onFocus: " << absY() << " " << absX() + 1;
  move(absY(), absX() + 1);
}

void bane::Button::onBlur() { termWindow_->showCursor(false); }
