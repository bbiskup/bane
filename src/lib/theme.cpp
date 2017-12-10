#include "theme.h"

#include <algorithm>
#include <ncurses.h>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
short colorPairIndex{0};
std::vector<std::pair<short, short>> nCursesColors;
} // namespace

bane::ColorPair::ColorPair(short nCursesForeground, short nCursesBackground)
    : nCursesForeground_{nCursesForeground}, nCursesBackground_{
                                                 nCursesBackground} {
  if (std::find(nCursesColors.begin(), nCursesColors.end(),
                std::make_pair(nCursesForeground, nCursesBackground)) ==
      nCursesColors.end()) {
    nCursesColorIndex_ = colorPairIndex++;
    init_pair(nCursesColorIndex_, nCursesForeground, nCursesBackground);
    nCursesColors.emplace_back(nCursesForeground, nCursesBackground);
  } else {
    throw std::runtime_error{"Non-unique color definition"};
  }
}

int bane::ColorPair::nCursesColorPair() const { return nCursesColorIndex_; }

const bane::ColorPair bane::color::white_on_blue{COLOR_WHITE, COLOR_BLUE};
const bane::ColorPair bane::color::yellow_on_green{COLOR_YELLOW, COLOR_GREEN};


bane::ColorPair bane::SimpleTheme::normal() const {
  return color::white_on_blue;
}
bane::ColorPair bane::SimpleTheme::active() const {
  return color::yellow_on_green;
}
