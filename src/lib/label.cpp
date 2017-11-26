#include "label.h"
#include <ncurses.h>

bane::Label::Label(std::string label) : label_{std::move(label)} {}

int bane::Label::preferredWidth() const noexcept { return static_cast<int>(label_.size()); }
int bane::Label::preferredHeight() const noexcept { return 1; }

void bane::Label::doRender() { mvwaddstr(window_, 0, 0, label_.c_str()); }
