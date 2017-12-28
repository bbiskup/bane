#include "widget.h"
#include "app.h"
#include "simple_layout_mgr.h"
#include "term_window.h"

#include <boost/core/demangle.hpp>
#include <boost/log/trivial.hpp>

#include <algorithm>
#include <functional>
#include <iterator>

namespace {
/// auto-incremented counter
int widgetNum{0};

int maxPreferredDim(const boost::ptr_vector<bane::Widget>& widgets,
                    std::function<int(const bane::Widget&)> dimGetter);

} // namespace

bane::Widget::Widget(Widget* root)
    : root_{root}, instanceNum_{widgetNum++}, layoutMgr_{
                                                  new SimpleLayoutMgr{*this}} {}

bane::Widget::~Widget() { BOOST_LOG_TRIVIAL(trace) << "Widget::~Widget"; }

std::string bane::Widget::id() const {
  return boost::core::demangle(typeid(*this).name()) + "_" +
         std::to_string(instanceNum_);
}

int bane::Widget::x() const noexcept { return x_; }

int bane::Widget::y() const noexcept { return y_; }

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
void bane::Widget::move(int x, int y) {
  x_ = x;
  y_ = y;
}
void bane::Widget::render() {
  BOOST_LOG_TRIVIAL(trace) << "render";
  layoutMgr_->layout();
  termWindow_->updateClickMap(*this);
  paintBackground();
  doRender();
  for (auto& child : children_) {
    child.render();
  }
}

bane::CharPoint bane::Widget::origin() const {
  if (parent_) {
    return {parent_->origin().x + x_, parent_->origin().y + y_};
  } else {
    return {x_, y_};
  }
}

void bane::Widget::setTermWindow(TermWindow& termWindow) {
  termWindow_ = &termWindow;
}

void bane::Widget::setApp(const App& app) { app_ = &app; }

/// Draw background color
void bane::Widget::paintBackground() {
  if (width_ <= 0 || height_ <= 0) {
    // before size adjustment?
    return;
  }
  BOOST_LOG_TRIVIAL(trace) << "paintBackground " << width_ << ", " << height_;
  CharPoint orig{origin()};
  attrset(COLOR_PAIR(1));
  std::string rowStr(static_cast<unsigned long>(width_), ' ');
  for (int y{orig.y}; y < orig.y + height_; ++y) {
    mvaddstr(y, x_, rowStr.c_str());
  }
  refresh();
}

/// \return number of children
size_t bane::Widget::numChildren() const noexcept { return children_.size(); }

/// Handle click event
boost::signals2::connection
bane::Widget::doOnClick(const OnClickSlotType& slot) {
  return onClick_.connect(slot);
}

/// Dispatch click event
void bane::Widget::click(int x, int y) { onClick_(x, y); }

/// Handle mouse release event
boost::signals2::connection
bane::Widget::doOnMouseRelease(const OnMouseReleaseSlotType& slot) {
  return onMouseRelease_.connect(slot);
}

/// Dispatch mouse release event
void bane::Widget::releaseMouse() { onMouseRelease_(); }

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
} // namespace
