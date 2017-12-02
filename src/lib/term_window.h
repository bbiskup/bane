#ifndef SCREEN_H
#define SCREEN_H

#include "widget.h"
#include <memory>
#include <vector>

namespace bane {

/// Abstraction of terminal
class TermWindow {
public:
  TermWindow();
  ~TermWindow();

  void updateSize();
  void updateClickMap(Widget& w);
  Widget* widgetAt(int x, int y) const;
  void waitForKey() const;

private:
  void setUpMouse();
  inline unsigned long clickMapIndex(int x, int y) const {
    return static_cast<unsigned long>(y * width_ + x);
  }

  int width_;
  int height_;
  /// Maintain a mapping of screen position to Widget instance
  /// to delegate mouse clicks
  /// position on screen (x, y) corresponds to
  /// y * width + x
  /// in vector
  std::unique_ptr<std::vector<Widget*>> clickMap_;
};
} // namespace bane

#endif
