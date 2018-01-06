#include "theme.h"


bane::ColorPair bane::SimpleTheme::normal() const {
  return color::white_on_black;
}
bane::ColorPair bane::SimpleTheme::active() const { return color::red_on_black; }

bane::ColorPair bane::SimpleTheme::engaged() const { return color::cyan_on_black; }

bane::ColorPair bane::SimpleTheme::blush() const { return color::white_on_blue; }
