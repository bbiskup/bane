#include "label.h"
#include "app.h"
#include <boost/log/trivial.hpp>
#include <iostream>

bane::Label::Label(Widget* parent, std::wstring label)
    : Widget{parent}, label_{std::move(label)} {}

int bane::Label::preferredWidth() const noexcept {
  return static_cast<int>(label_.size());
}
int bane::Label::preferredHeight() const noexcept { return 1; }

/// Set label text
void bane::Label::setText(std::wstring text) {
  label_ = std::move(text);
  doRender();
}

void bane::Label::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "Label::doRender " << relX() << " " << relY();
  // attrset(app_->theme().normal().nCursesColorPair());
  *termWindow_ << Font::normal << label_;
}
