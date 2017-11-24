#include "label.h"
#include <ncurses.h>

bane::Label::Label(std::string label) : label_{std::move(label)} {}

void bane::Label::doRender() { mvwaddstr(window_, 0, 0, label_.c_str()); }
