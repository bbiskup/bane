#ifndef COLOR_PAIR_H
#define COLOR_PAIR_H

#include "ncurses.h"

namespace bane {
/// Foreground/background color for widgets
class ColorPair {
public:
  ColorPair(short nCursesForeground, short nCursesBackground);
  chtype nCursesColorPair() const;

private:
  const short nCursesForeground_;
  const short nCursesBackground_;
  short nCursesColorIndex_;
  chtype nCursesColorPair_;
};

namespace color {
extern const ColorPair white_on_blue;
extern const ColorPair white_on_black;
extern const ColorPair yellow_on_red;
extern const ColorPair yellow_on_green;
extern const ColorPair red_on_blue;
extern const ColorPair red_on_black;
extern const ColorPair cyan_on_blue;
extern const ColorPair cyan_on_black;
} // namespace color
} // namespace bane

#endif /* COLOR_PAIR_H */
