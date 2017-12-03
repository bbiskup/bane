#include "label.h"
#include <iostream>
#include <ncurses.h>

bane::Label::Label(Widget* root, std::string label) : Widget{root}, label_{std::move(label)} {}

int bane::Label::preferredWidth() const noexcept {
  return static_cast<int>(label_.size());
}
int bane::Label::preferredHeight() const noexcept { return 1; }

void bane::Label::doRender() {
  //std::cout << "Label::doRender" << y() << " " << x() << std::endl;
  mvwaddstr(window_, 0, 0, label_.c_str());
}
