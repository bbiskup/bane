#include "color_pair.h"

#include <algorithm>
#include <ncurses.h>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
short colorPairIndex{1};
std::vector<std::pair<short, short>> nCursesColors;
} // namespace

bane::ColorPair::ColorPair(short nCursesForeground, short nCursesBackground)
    : nCursesForeground_{nCursesForeground}, nCursesBackground_{
                                                 nCursesBackground} {
  if (nCursesColors.size() == 0) {
    initscr();
    start_color(); // must come before creating windows
  }
  if (std::find(nCursesColors.begin(), nCursesColors.end(),
                std::make_pair(nCursesForeground_, nCursesBackground_)) ==
      nCursesColors.end()) {
    nCursesColorIndex_ = colorPairIndex++;
    init_pair(nCursesColorIndex_, nCursesForeground_, nCursesBackground_);
    nCursesColors.emplace_back(nCursesForeground_, nCursesBackground_);
    nCursesColorPair_ = COLOR_PAIR(nCursesColorIndex_);
  } else {
    throw std::runtime_error{"Non-unique color definition"};
  }
}

chtype bane::ColorPair::nCursesColorPair() const { return nCursesColorPair_; }

const bane::ColorPair bane::color::white_on_blue{COLOR_WHITE, COLOR_BLUE};
const bane::ColorPair bane::color::white_on_black{COLOR_WHITE, COLOR_BLACK};
const bane::ColorPair bane::color::yellow_on_green{COLOR_YELLOW, COLOR_GREEN};
const bane::ColorPair bane::color::yellow_on_red{COLOR_YELLOW, COLOR_RED};
const bane::ColorPair bane::color::red_on_blue{COLOR_RED, COLOR_BLUE};
const bane::ColorPair bane::color::red_on_black{COLOR_RED, COLOR_BLACK};
const bane::ColorPair bane::color::cyan_on_blue{COLOR_CYAN, COLOR_BLUE};
const bane::ColorPair bane::color::cyan_on_black{COLOR_CYAN, COLOR_BLACK};
