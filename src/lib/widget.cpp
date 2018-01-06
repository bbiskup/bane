#include "widget.h"
#include "app.h"
#include "simple_layout_mgr.h"

#include <boost/core/demangle.hpp>
#include <boost/log/trivial.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <thread>

using namespace std::chrono_literals;

namespace {
/// auto-incremented counter
int widgetNum{0};

int maxPreferredDim(const boost::ptr_vector<bane::Widget>& widgets,
                    std::function<int(const bane::Widget&)> dimGetter);

void ensureAcceptsFocus(const bane::Widget* w);

} // namespace

bane::Widget::Widget(Widget* root)
    : root_{root}, layoutMgr_{new SimpleLayoutMgr{*this}}, instanceNum_{
                                                               widgetNum++} {}

bane::Widget::~Widget() { BOOST_LOG_TRIVIAL(trace) << "Widget::~Widget"; }

std::string bane::Widget::id() const {
  return boost::core::demangle(typeid(*this).name()) + "_" +
         std::to_string(instanceNum_);
}

/// X coordinate relative to parent widget
int bane::Widget::relX() const noexcept { return x_; }

/// Y coordinate relative to parent widget
int bane::Widget::relY() const noexcept { return y_; }

/// X coordinate with respect to terminal window origin
int bane::Widget::absX() const noexcept {
  if (parent_) {
    return parent_->absX() + relX();
  } else {
    return relX();
  }
}

/// Y coordinate with respect to terminal window origin
int bane::Widget::absY() const noexcept {
  if (parent_) {
    return parent_->absY() + relY();
  } else {
    return relY();
  }
}

int bane::Widget::width() const noexcept { return width_; }

int bane::Widget::height() const noexcept { return height_; }

/// return largest preferred width of any child
int bane::Widget::maxPreferredChildWidth() const noexcept {
  return maxPreferredDim(children_,
                         [](const Widget& w) { return w.preferredWidth(); });
}

/// return largest preferred width of any child
int bane::Widget::maxPreferredChildHeight() const noexcept {
  return maxPreferredDim(children_,
                         [](const Widget& w) { return w.preferredHeight(); });
}

bool bane::Widget::hasFocus() const { return app_->focusWidget() == this; }

void bane::Widget::requestFocus() {
  ensureAcceptsFocus(this);
  app_->requestFocus(this);
}
void bane::Widget::yieldFocus(FocusYieldHint yieldHint) {
  app_->yieldFocus(this, yieldHint);
}

void bane::Widget::setFocusPredecessor(Widget* predecessor) {
  ensureAcceptsFocus(this);
  ensureAcceptsFocus(predecessor);
  focusPredecessor_ = predecessor;
  predecessor->focusSuccessor_ = this;
}

void bane::Widget::setFocusSuccessor(Widget* successor) {
  ensureAcceptsFocus(this);
  ensureAcceptsFocus(successor);
  focusSuccessor_ = successor;
  successor->focusPredecessor_ = this;
}

bane::Widget* bane::Widget::focusPredecessor() const {
  return focusPredecessor_;
}

bane::Widget* bane::Widget::focusSuccessor() const { return focusSuccessor_; }

void bane::Widget::resize(int width, int height) {
  width_ = width;
  height_ = height;
}

void bane::Widget::resizeToPreferred() {
  const int w{preferredWidth()};
  const int h{preferredHeight()};
  BOOST_LOG_TRIVIAL(trace) << "Widget::resizeToPreferred " << w << ", " << h;
  resize(w, h);
}

/// Move widget to new position on screen
void bane::Widget::moveTo(int x, int y) {
  x_ = x;
  y_ = y;
}

void bane::Widget::moveTo(const CharPoint& p) {
  x_ = p.x;
  y_ = p.y;
}

void bane::Widget::render() {
  BOOST_LOG_TRIVIAL(trace) << "render";
  layoutMgr_->layout();
  termWindow_->updateClickMap(*this);
  paintBackground();

  termWindow_->move(origin());
  *termWindow_ << app_->theme().normal();

  if (blush_) {
    // Don't override block rectangle when debugging layout
    refresh();
    std::this_thread::sleep_for(20ms);
  }

  doRender();
  for (auto& child : children_) {
    child.render();
  }

  Widget* focusWidget{app_->focusWidget()};
  if (focusWidget) {
    termWindow_->showCursor(focusWidget->showCursorWhenFocus());
    focusWidget->onFocus();
    //  refresh();
  }
}

bane::CharPoint bane::Widget::origin() const {
  if (parent_) {
    return {parent_->origin().x + x_, parent_->origin().y + y_};
  } else {
    return {x_, y_};
  }
}

/// Convert screen coordinates to in-widget coordinates
bane::CharPoint bane::Widget::screenToRelative(int x, int y) {
  return {x - absX(), y - absY()};
}

void bane::Widget::setTermWindow(TermWindow* termWindow) {
  termWindow_ = termWindow;
}

/// If true, widget is painted in a solid color.
/// This is useful for debugging layout and rendering.
void bane::Widget::blush(bool isBlush) {
  blush_ = isBlush && app_->isDebug();
  render();
}

void bane::Widget::setApp(App& app) { app_ = &app; }

/// Draw background color
void bane::Widget::paintBackground() {
  if (width_ <= 0 || height_ <= 0) {
    // before size adjustment?
    return;
  }
  BOOST_LOG_TRIVIAL(trace) << "paintBackground " << width_ << ", " << height_;
  CharPoint orig{origin()};
  termWindow_->move(orig);
  *termWindow_ << (blush_ ? termWindow_->theme().blush()
                          : termWindow_->theme().normal());
  std::string rowStr(static_cast<unsigned long>(width_), ' ');
  for (int y{orig.y}; y < orig.y + height_; ++y) {
    mvaddstr(y, x_, rowStr.c_str());
  }
  refresh();
}

/// \return number of children
size_t bane::Widget::numChildren() const noexcept { return children_.size(); }

/// \return next sibling, or nullptr if this Widget is last child of parent
bane::Widget* bane::Widget::nextSibling() {
  if (!parent_) {
    return nullptr;
  }
  auto thisIter =
      std::find(parent_->children_.begin(), parent_->children_.end(), *this);
  ++thisIter;
  return thisIter != parent_->children_.end() ? &*thisIter : nullptr;
}

bane::Widget* bane::Widget::previousSibling() {
  if (!parent_) {
    return nullptr;
  }
  auto thisIter =
      std::find(parent_->children_.begin(), parent_->children_.end(), *this);
  if (thisIter == parent_->children_.begin()) {
    return nullptr;
  }
  --thisIter;
  return &*thisIter;
}

/// Handle mouse event
boost::signals2::connection
bane::Widget::doOnMouse(const OnMouseSlotType& slot) const {
  return onMouse_.connect(slot);
}

/// Dispatch mouse event
void bane::Widget::mouse(const MouseEvent& mouseEvent) { onMouse_(mouseEvent); }

/// Handle key event
boost::signals2::connection
bane::Widget::doOnKey(const OnKeySlotType& slot) const {
  return onKey_.connect(slot);
}

/// Dispatch key event
void bane::Widget::key(const KeyEvent& keyEvent) { onKey_(keyEvent); }

/// Handle change event
boost::signals2::connection
bane::Widget::doOnChange(const OnChangeSlotType& slot) const {
  return onChange_.connect(slot);
}

/// Dispatch change event
void bane::Widget::change() { onChange_(this); }

std::ostream& bane::operator<<(std::ostream& strm, const Widget& w) {
  return strm << w.id();
}

namespace {
int maxPreferredDim(const boost::ptr_vector<bane::Widget>& widgets,
                    std::function<int(const bane::Widget&)> dimGetter) {
  if (widgets.empty()) {
    return 0;
  }

  std::vector<int> widths;
  std::transform(
      widgets.begin(), widgets.end(), std::back_inserter(widths),
      [&dimGetter](const bane::Widget& widget) { return dimGetter(widget); });
  return *std::max_element(widths.begin(), widths.end());
}

void ensureAcceptsFocus(const bane::Widget* w) {
  if (!w->acceptsFocus()) {
    throw std::runtime_error{"Widget " + w->id() + " does not accept focus"};
  }
}
} // namespace
