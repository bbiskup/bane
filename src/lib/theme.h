#ifndef THEME_H
#define THEME_H

namespace bane {

/// Foreground/background color for widgets
class ColorPair {
public:
  ColorPair(short nCursesForeground, short nCursesBackground);
  int nCursesColorPair() const;

private:
  const short nCursesForeground_;
  const short nCursesBackground_;
  short nCursesColorIndex_;
};

namespace color {
extern const ColorPair white_on_blue;
extern const ColorPair yellow_on_green;
} // namespace color

/// GUI colors and appearance
class Theme {
public:
  virtual ~Theme() = default;

  /// Normal color combination
  virtual ColorPair normal() const = 0;

  /// ColorPair combination for active elements (e.g. buttons)
  virtual ColorPair active() const = 0;
};

class SimpleTheme : public Theme {

public:
  using Theme::Theme;
  ColorPair normal() const override;
  ColorPair active() const override;
};
} // namespace bane

#endif /* THEME_H */
