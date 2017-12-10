#include "widget.h"
#include "simple_layout_mgr.h"
#include "term_window.h"

#include <boost/core/demangle.hpp>
#include <boost/log/trivial.hpp>

namespace {
/// auto-incremented counter
int widgetNum{0};

} // namespace

bane::Widget::Widget(Widget* root)
    : root_{root}, id_{makeWidgetId()}, layoutMgr_{new SimpleLayoutMgr} {}

bane::Widget::~Widget() { BOOST_LOG_TRIVIAL(trace) << "Widget::~Widget"; }

const std::string& bane::Widget::id() const { return id_; }

int bane::Widget::x() const noexcept { return x_; }

int bane::Widget::y() const noexcept { return y_; }

int bane::Widget::width() const noexcept { return width_; }

int bane::Widget::height() const noexcept { return height_; }

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
  layoutMgr_->layout(*this, children_);
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

/// Draw background color
void bane::Widget::paintBackground() {
  BOOST_LOG_TRIVIAL(trace) << "paintBackground " << width_ << ", " << height_;
  CharPoint orig{origin()};
  attrset(COLOR_PAIR(1));
  std::string rowStr(static_cast<unsigned long>(width_), ' ');
  for (int y{orig.y}; y < orig.y + height_; ++y) {
    mvaddstr(y, x_, rowStr.c_str());
  }
  refresh();
}

/// Handle click event
boost::signals2::connection
bane::Widget::doOnClick(const OnClickSlotType& slot) {
  return onClick_.connect(slot);
}

/// Dispatch click event
void bane::Widget::click(int x, int y) { onClick_(x, y); }

/// Create a unique Widget identifier.
std::string bane::Widget::makeWidgetId() const {
    std::string result{std::string{boost::core::demangle(typeid(*this).name())} + "_" +
         std::to_string(widgetNum)};
    ++widgetNum;
    return result;
}

std::ostream& bane::operator<<(std::ostream& strm, const Widget& w) {
  return strm << w.id();
}
