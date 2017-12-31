#include "stateful_button.h"
#include "term/term_window.h"

#include <boost/log/trivial.hpp>

bane::StatefulButton::StatefulButton(Widget* root, bool state)
    : Widget{root}, state_{state} {}

void bane::StatefulButton::toggleState() {
  state_ = !state_;
  render();
}

void bane::StatefulButton::setState(bool state) {
  if (state_ != state) {
    state_ = state;
    render();
  }
}

void bane::StatefulButton::onFocus() {
  BOOST_LOG_TRIVIAL(trace) << "StatefulButton::onFocus: " << absY() << " "
                           << absX() + 1;
  move(absY(), absX() + 1);
}

void bane::StatefulButton::onBlur() { termWindow_->showCursor(false); }
