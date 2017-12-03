#include "widget.h"
#include "simple_layout_mgr.h"

#include <boost/log/trivial.hpp>
#include <iostream>

bane::Widget::Widget(Widget* root)
    : root_{root}, layoutMgr_{new SimpleLayoutMgr} {}

bane::Widget::~Widget() {
  BOOST_LOG_TRIVIAL(trace) << "Widget::~Widget";
  if (window_) {
    delwin(window_);
  }
}

int bane::Widget::x() const noexcept { return x_; }

int bane::Widget::y() const noexcept { return y_; }

int bane::Widget::width() const noexcept { return width_; }

int bane::Widget::height() const noexcept { return height_; }

void bane::Widget::resize(int width, int height) {
  width_ = width;
  height_ = height;
  createWindow();
}

void bane::Widget::resizeToPreferred() {
  const int w{preferredWidth()};
  const int h{preferredHeight()};
  BOOST_LOG_TRIVIAL(trace) << "Widget::resizeToPreferred " << w << ", " << h;
  resize(w, h);
}

/// Move widget to new position on screen
void bane::Widget::move(int x, int y) {
  x_ = x;
  y_ = y;
  createWindow();
}

void bane::Widget::render() {
  BOOST_LOG_TRIVIAL(trace) << "render";
  layoutMgr_->layout(*this, children_);
  doRender();
  touchwin(window_); // TODO avoid touch if possible
  wrefresh(window_);
  for (auto& child : children_) {
    child.render();
  }
}

/// Handle click event
boost::signals2::connection
bane::Widget::doOnClick(const OnClickSlotType& slot) {
  return onClick_.connect(slot);
}

/// Dispatch click event
void bane::Widget::click(int x, int y) { onClick_(x, y); }

WINDOW* bane::Widget::parentWindow() {
  return parent_ ? parent_->window_ : stdscr;
}

/// A new ncurses window is created every time the widget gets resized
void bane::Widget::createWindow() {
  if (width_ == 0 || height_ == 0) {
  }
  if (window_) {
    delwin(window_);
  }
  BOOST_LOG_TRIVIAL(trace) << "Widget::createWindow " << height_ << " "
                           << width_;
  window_ = derwin(parentWindow(), height_, width_, y_, x_);

  init_pair(1, COLOR_BLUE, COLOR_WHITE);
  wbkgd(window_, COLOR_PAIR(1));
  // wrefresh(window_);
}
