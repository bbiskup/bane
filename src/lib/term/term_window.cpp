#include "term_window.h"
#include <boost/log/trivial.hpp>
#include <stdexcept>

bane::TermWindow::TermWindow(std::unique_ptr<Theme> theme)
    : theme_{std::move(theme)} {}

bane::TermWindow::~TermWindow() {}

/// Indicate area occupied by Widget
void bane::TermWindow::updateClickMap(Widget& widget) {
  int w{widget.width()};
  int h{widget.height()};
  int xOrigin{widget.absX()};
  int yOrigin{widget.absY()};
  BOOST_LOG_TRIVIAL(trace) << "updateClickMap " << widget.id() << " " << w
                           << "x" << h << "+" << xOrigin << "+" << yOrigin;
  Widget* widgetAddr{&widget};

  // Tolerate out-of-screen updates
  // (A widget may be partially outside the viewport)
  if (w >= width_ || h >= height_) {
    return;
  }

  // direct handle for loop
  std::vector<Widget*>* clickMap{clickMap_.get()};

  for (int x{0}; x < w; ++x) {
    for (int y{}; y < h; ++y) {
      clickMap->at(clickMapIndex(xOrigin + x, yOrigin + y)) = widgetAddr;
    }
  }
}

bane::Widget* bane::TermWindow::widgetAt(int x, int y) const {
  return clickMap_->at(clickMapIndex(x, y));
}

void bane::TermWindow::updateSize() {
  CharPoint screenDims{screenDimensions()};
  width_ = screenDims.x;
  height_ = screenDims.y;
  BOOST_LOG_TRIVIAL(trace) << "updateSize " << width_ << ", " << height_;
  clickMap_.reset(
      new std::vector<Widget*>{static_cast<unsigned long>(width_ * height_)});
  // TODO repaint all widgets
}

/// Apply multiple font styles at once
bane::TermWindow& bane::TermWindow::operator<<(const FontStyles& fontStyles) {
  for (Font f : fontStyles) {
    *this << f;
  }
  return *this;
}
