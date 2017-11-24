#ifndef WIDGET_H
#define WIDGET_H

#include "layout_mgr.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <memory>
#include <ncurses.h>

namespace bane {

class Widget {
public:
  Widget();
  virtual ~Widget() = default;
  int x() const noexcept;
  int y() const noexcept;
  void resize(int width, int height);
  void move(int x, int y);
  void render();
  virtual void doRender() {}

protected:
  WINDOW* window_{};

private:
  void createWindow();

  int x_{};
  int y_{};
  int width_{};
  int height_{};
  std::unique_ptr<LayoutMgr> layoutMgr_;
  boost::ptr_vector<Widget> children_;
};

} // namespace bane

#endif /* WIDGET_H */
