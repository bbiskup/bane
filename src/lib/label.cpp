#include "label.h"
#include "app.h"
#include <boost/log/trivial.hpp>
#include <iostream>
#include <ncurses.h>

bane::Label::Label(Widget* root, std::string label)
    : Widget{root}, label_{std::move(label)} {}

int bane::Label::preferredWidth() const noexcept {
  return static_cast<int>(label_.size());
}
int bane::Label::preferredHeight() const noexcept { return 1; }

/// Set label text
void bane::Label::setText(std::string text){
    label_ = std::move(text);
    doRender();
}

void bane::Label::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "Label::doRender " << relX() << " " << relY();
  CharPoint orig{origin()};
  attrset(app_->theme().normal().nCursesColorPair());
  mvaddstr(orig.y, orig.x, label_.c_str());
}

