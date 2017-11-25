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

  void waitForKey() const;

private:
  /// Maintain a mapping of screen position to Widget instance
  /// to delegate mouse clicks
  /// position on screen (x, y) corresponds to
  /// y * width + x
  /// in vector
  std::unique_ptr<std::vector<Widget*>> clickMap_;
};
} // namespace bane

#endif
