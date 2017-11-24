#include "widget.h"
#include "simple_layout_mgr.h"

bane::Widget::Widget() : layoutMgr_{new SimpleLayoutMgr}{}

int bane::Widget::x() const noexcept { return x_; }
int bane::Widget::y() const noexcept { return y_; }
void bane::Widget::resize(int width, int height) {
  width_ = width;
  height_ = height;
  createWindow();
}
void bane::Widget::move(int x, int y) {
  x_ = x;
  y_ = y;
}

void bane::Widget::render() {
  layoutMgr_->layout(*this, children_);
  for (auto& child : children_) {
    child.render();
  }
  doRender();
  wrefresh(window_);
}

void bane::Widget::createWindow() {
  if (width_ == 0 || height_ == 0) {
  }
  if (window_) {
    delwin(window_);
  }
  window_ = newwin(height_, width_, y_, x_);
}
