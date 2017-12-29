#include "stateful_button.h"
#include "term_window.h"

#include <boost/log/trivial.hpp>

void bane::StatefulButton::onFocus() {
  BOOST_LOG_TRIVIAL(trace) << "StatefulButton::onFocus: " << absY() << " " << absX() + 1;
  move(absY(), absX() + 1);
}

void bane::StatefulButton::onBlur() { termWindow_->showCursor(false); }
