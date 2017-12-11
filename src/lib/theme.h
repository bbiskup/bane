#ifndef THEME_H
#define THEME_H

#include <ncurses.h>

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
extern const ColorPair yellow_on_red;
extern const ColorPair yellow_on_green;
extern const ColorPair red_on_blue;
extern const ColorPair cyan_on_blue;
} // namespace color

/// GUI colors and appearance
class Theme {
public:
  virtual ~Theme() = default;

  /// Normal color combination
  virtual ColorPair normal() const = 0;

  /// ColorPair combination for active elements (e.g. buttons)
  /// in unused state
  virtual ColorPair active() const = 0;
  
  /// ColorPair combination for active elements (e.g. buttons)
  /// in used state (e.g. button while pressed)
  virtual ColorPair engaged() const = 0;
};

class SimpleTheme : public Theme {

public:
  using Theme::Theme;
  ColorPair normal() const override;
  ColorPair active() const override;
  ColorPair engaged() const override;
};
} // namespace bane

#endif /* THEME_H */
