#ifndef TERM_WINDOW_H
#define TERM_WINDOW_H

#include "widget.h"

#include <memory>
#include <vector>
#include <string>

namespace bane {

enum class Font { normal, bold, underline, dim, reverse };

using FontStyles = std::vector<Font>;
using TerminalText = std::string;

/// Abstraction of terminal
class TermWindow {
public:
  TermWindow();
  virtual ~TermWindow();

  void updateSize();
  void updateClickMap(Widget& w);
  Widget* widgetAt(int x, int y) const;
  int width() const{return width_;}
  int height() const{return height_;}

  /// Wait until a key has been pressed
  virtual void waitForKey() const = 0;

  /// Whether or not cursor should be displayed
  virtual void showCursor(bool show=true) = 0;

  /// Move cursor to given position
  virtual void move(int x, int y) = 0;

  /// Refresh screen
  virtual void refresh() = 0;

  /// Draw a string at given absolute position
  virtual void drawString(int x, int y, const TerminalText& text) = 0;
  void drawString(const CharPoint& charPoint, const TerminalText& text){
      drawString(charPoint.x, charPoint.y, text);
  }

  /// Emit text, applying currently set font style
  virtual TermWindow& operator<<(const std::string s) = 0;

  /// Set font style
  virtual TermWindow& operator<<(Font fontStyle) = 0;
  TermWindow& operator<<(const FontStyles& fontStyles);

  virtual CharPoint screenDimensions() const = 0;

protected:
  /// Configure terminal to accept mouse input
  virtual void setUpMouse() = 0;

private:
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
