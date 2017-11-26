#ifndef WIDGET_H
#define WIDGET_H

#include "layout_mgr.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <memory>
#include <ncurses.h>

namespace bane {

class Widget {
public:
  enum WidgetSize : int {
    /// use available space
    expand = -1,
  };

  Widget();
  virtual ~Widget();
  int x() const noexcept;
  int y() const noexcept;
  int width() const noexcept;
  int height() const noexcept;
  virtual int preferredWidth() const noexcept = 0;
  virtual int preferredHeight() const noexcept = 0;

  void resize(int width, int height);
  void resizeToPreferred();
  void move(int x, int y);
  void render();

  template <class LayoutMgrT> void setLayoutMgr() {
    layoutMgr_.reset(new LayoutMgrT);
  }

  template <typename WidgetT, typename... Args> void addChild(Args&&... args) {
    Widget* newWidget = new WidgetT{args...};
    newWidget->parent_ = this;
    children_.push_back(newWidget);
  }

protected:
  WINDOW* window_{};
  virtual void doRender() {}

private:
  void createWindow();

  Widget* parent_{};
  int x_{};
  int y_{};
  int width_{};
  int height_{};
  std::unique_ptr<LayoutMgr> layoutMgr_;
  boost::ptr_vector<Widget> children_;
};

} // namespace bane

#endif /* WIDGET_H */
