#include "widget.h"
#include "simple_layout_mgr.h"
#include <iostream>

bane::Widget::Widget() : layoutMgr_{new SimpleLayoutMgr} {}

bane::Widget::~Widget() {
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
  resize(preferredWidth(), preferredHeight());
}

void bane::Widget::move(int x, int y) {
  x_ = x;
  y_ = y;
  createWindow();
}

void bane::Widget::render() {
  layoutMgr_->layout(*this, children_);
  doRender();
  touchwin(window_); // TODO avoid touch if possible
  wrefresh(window_);
  for (auto& child : children_) {
    child.render();
  }
}

WINDOW* bane::Widget::parentWindow(){
  return  parent_ ? parent_->window_ : stdscr;
}

/// A new ncurses window is created everytime the widget gets resized
void bane::Widget::createWindow() {
  if (width_ == 0 || height_ == 0) {
  }
  if (window_) {
    delwin(window_);
  }
  // std::cout << "Widget::createWindow" << height_ << " " << width_ <<
  // std::endl;
  window_ = derwin(parentWindow(), height_, width_, y_, x_);

  init_pair(1, COLOR_BLUE, COLOR_WHITE);
  wbkgd(window_, COLOR_PAIR(1));
  //wrefresh(window_);
}
