#ifndef WIDGET_H
#define WIDGET_H

#include "layout_mgr.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signals2.hpp>
#include <iostream>
#include <memory>

namespace bane {

/// A character position
/// (on screen or within window)
struct CharPoint {
  int x;
  int y;
};

class App;
class TermWindow;
class MouseEvent;
class KeyEvent;

/// Indicate whether the focus was yielded by moving
/// before or after widget. This information is used to decide
/// which widget should receive focus next
enum class FocusYieldHint { start, end };

class Widget {
public:
  enum WidgetSize : int {
    /// use available space
    expand = -1,
  };

  explicit Widget(Widget* root = nullptr);
  virtual ~Widget();

  std::string id() const;

  int relX() const noexcept;
  int relY() const noexcept;
  int absX() const noexcept;
  int absY() const noexcept;
  int width() const noexcept;
  int height() const noexcept;
  virtual int preferredWidth() const noexcept = 0;
  virtual int preferredHeight() const noexcept = 0;

  int maxPreferredChildWidth() const noexcept;
  int maxPreferredChildHeight() const noexcept;

  virtual bool acceptsFocus() const { return false; }
  virtual bool showCursorWhenFocus() const { return false; }
  virtual void onFocus() {}
  virtual void onBlur() {}
  bool hasFocus() const;
  void requestFocus();
  void yieldFocus(FocusYieldHint yieldHint);
  void setFocusPredecessor(Widget* successor);
  void setFocusSuccessor(Widget* successor);
  Widget* focusPredecessor() const;
  Widget* focusSuccessor() const;

  void resize(int width, int height);
  void resizeToPreferred();
  void moveTo(int x, int y);
  void moveTo(const CharPoint& point);
  void render();
  Widget* root() { return root_ ? root_ : this; }
  CharPoint origin() const;
  CharPoint screenToRelative(int x, int y);
  void setApp(App& app);
  void setTermWindow(TermWindow* termWindow);

  void blush(bool isBlush);

  template <class LayoutMgrT> void setLayoutMgr() {
    layoutMgr_.reset(new LayoutMgrT{*this});
  }

  /// Add a child widget. Arguments will be forwarded to the constructor
  /// of the concrete Widget subclass.
  /// \return non-owning pointer to newly created widget
  template <typename WidgetT, typename... Args>
  WidgetT* addChild(Args&&... args) {
    Widget* newWidget = new WidgetT{root_, args...};
    onAddChild(*newWidget);
    newWidget->parent_ = this;
    newWidget->app_ = app_;
    newWidget->termWindow_ = termWindow_;
    children_.push_back(newWidget);
    render();
    return static_cast<WidgetT*>(newWidget);
  }

  // Signals & slots
  using OnMouse = boost::signals2::signal<void(const MouseEvent& mouseEvent)>;
  using OnMouseSlotType = OnMouse::slot_type;
  boost::signals2::connection doOnMouse(const OnMouseSlotType& slot) const;
  void mouse(const MouseEvent& e);

  using OnKey = boost::signals2::signal<void(const KeyEvent& keyEvent)>;
  using OnKeySlotType = OnKey::slot_type;
  boost::signals2::connection doOnKey(const OnKeySlotType& slot) const;
  void key(const KeyEvent& e);

  using OnChange = boost::signals2::signal<void(Widget*)>;
  using OnChangeSlotType = OnChange::slot_type;
  boost::signals2::connection doOnChange(const OnChangeSlotType& slot) const;
  void change();

  boost::ptr_vector<Widget>& children() { return children_; }
  size_t numChildren() const noexcept;

  Widget* nextSibling();
  Widget* previousSibling();

  bool operator==(const Widget& rhs) const { return id() == rhs.id(); }

  friend std::ostream& operator<<(std::ostream& strm, const Widget& w);
  friend class LayoutMgr;

protected:
  virtual void doRender() {}
  void paintBackground();
  virtual void onAddChild(Widget&) {}

  Widget* root_{};
  Widget* focusPredecessor_{};
  Widget* focusSuccessor_{};
  App* app_{};
  TermWindow* termWindow_{};
  std::unique_ptr<LayoutMgr> layoutMgr_;

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
  boost::ptr_vector<Widget> children_;
  bool blush_{false};

  mutable OnMouse onMouse_;
  mutable OnKey onKey_;
  mutable OnChange onChange_;
};

} // namespace bane

#endif /* WIDGET_H */
