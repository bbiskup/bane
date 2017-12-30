#include "line_edit.h"
#include "event/mouse_event.h"
#include "term_window.h"

#include <boost/log/trivial.hpp>

namespace {
/// Separator between label and text
const std::string labelSeparator = ": ";
} // namespace

bane::LineEdit::LineEdit(Widget* root, std::string label, int textFieldWidth,
                         std::string text)
    : Widget{root}, label_{label}, textFieldWidth_{textFieldWidth}, text_{
                                                                        text} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "LineEdit: on mouse";
    if (e.clickType == mouse::ClickType::single ||
        e.clickType == mouse::ClickType::release) {
      positionCursor(e.x, e.y);
    }
  });
}

int bane::LineEdit::preferredWidth() const noexcept {
  return static_cast<int>(label_.size() + labelSeparator.size() + text_.size());
}

int bane::LineEdit::preferredHeight() const noexcept { return 1; }

void bane::LineEdit::setLabel(std::string label) { label_ = std::move(label); }

void bane::LineEdit::setText(std::string text) { text_ = std::move(text); }

void bane::LineEdit::setTextFieldWidth(int width) { textFieldWidth_ = width; }

void bane::LineEdit::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::doRender " << relX() << " " << relY();

  CharPoint orig{origin()};
  mvaddstr(orig.y, orig.x, (label_ + labelSeparator + text_).c_str());
}

void bane::LineEdit::onFocus() {
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::onFocus: " << absY() << " "
                           << absX() + 1;
  move(absY(), absX() + static_cast<int>(textStartOffset()));
}

void bane::LineEdit::onBlur() { termWindow_->showCursor(false); }

unsigned long bane::LineEdit::textStartOffset() const {
  // Label, colon, space
  return label_.size() + labelSeparator.size();
}

void bane::LineEdit::positionCursor(int x, int y) {
  CharPoint rel{screenToRelative(x, y)};
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::positionCursor " << x << ", " << y
                           << " " << cursorPos_;
  BOOST_LOG_TRIVIAL(trace) << "  rel " << rel.x << ", " << rel.y << " "
                           << cursorPos_;
  int textOffset{static_cast<int>(textStartOffset())};
  int newRelX;
  if (rel.x < textOffset) {
    // If label was clicked, move cursor to first character position
    newRelX = textOffset;
  } else {
    newRelX = rel.x;
  }
  move(absY(), absX() + static_cast<int>(newRelX));
}
