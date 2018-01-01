#ifndef THEME_H
#define THEME_H

#include "color_pair.h"

#include <ncurses.h>

namespace bane {


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
