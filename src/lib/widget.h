#ifndef WIDGET_H
#define WIDGET_H

#include "layout_mgr.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signals2.hpp>
#include <iostream>
#include <memory>
#include <ncurses.h>

namespace bane {

/// A character position
/// (on screen or within window)
struct CharPoint {
  int x;
  int y;
};

class App;
class TermWindow;

class Widget {
public:
  enum WidgetSize : int {
    /// use available space
    expand = -1,
  };

  explicit Widget(Widget* root = nullptr);
  virtual ~Widget();

  std::string id() const;

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
  Widget* root() { return root_ ? root_ : this; }
  CharPoint origin() const;
  void setApp(const App& app);
  void setTermWindow(TermWindow& termWindow);

  template <class LayoutMgrT> void setLayoutMgr() {
    layoutMgr_.reset(new LayoutMgrT);
  }

  /// Add a child widget. Arguments will be forwarded to the constructor
  /// of the concrete Widget subclass.
  /// \return non-owning pointer to newly created widget
  template <typename WidgetT, typename... Args>
  WidgetT* addChild(Args&&... args) {
    Widget* newWidget = new WidgetT{root_, args...};
    newWidget->parent_ = this;
    newWidget->app_ = app_;
    newWidget->termWindow_ = termWindow_;
    children_.push_back(newWidget);
    render();
    return static_cast<WidgetT*>(newWidget);
  }

  // Signals & slots
  using OnClick = boost::signals2::signal<void(int x, int y)>;
  using OnClickSlotType = OnClick::slot_type;

  boost::signals2::connection doOnClick(const OnClickSlotType& slot);

  void click(int x, int y);

  friend std::ostream& operator<<(std::ostream& strm, const Widget& w);

protected:
  Widget* root_{};
  const App* app_{};
  TermWindow* termWindow_{};
  virtual void doRender() {}
  void paintBackground();

private:
  void createWindow();

  Widget* parent_{};
  const int instanceNum_;

  // horizontal position of
  // top left corner, in screen coordinates
  int x_{};

  // vertical position of top left corner, in screen coordinates
  int y_{};

  int width_{};
  int height_{};
  std::unique_ptr<LayoutMgr> layoutMgr_;
  boost::ptr_vector<Widget> children_;

  OnClick onClick_;
};

} // namespace bane

#endif /* WIDGET_H */
