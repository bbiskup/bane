#include "line_edit.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "term_window.h"

#include <boost/log/trivial.hpp>

#include <algorithm>

namespace {
/// Separator between label and text
const std::string labelSeparator = ": ";
} // namespace

bane::LineEdit::LineEdit(Widget* root, std::string label, size_t textFieldWidth,
                         std::string text)
    : Widget{root}, label_{label}, textFieldWidth_{textFieldWidth}, text_{
                                                                        text} {
  doOnMouse([this](const MouseEvent& e) {
    BOOST_LOG_TRIVIAL(trace) << "LineEdit: on mouse";
    if (e.clickType == mouse::ClickType::single ||
        e.clickType == mouse::ClickType::release) {
      CharPoint rel{screenToRelative(e.x, e.y)};
      positionCursorInWidget(static_cast<size_t>(rel.x));
    }
  });
  doOnKey([this](const KeyEvent& e) {
    if (e.specialKey) {
      handleSpecialKey(*e.specialKey);
    } else {
      handleTextKey(e.c);
    }
  });
}

int bane::LineEdit::preferredWidth() const noexcept {
  return static_cast<int>(
      label_.size() + labelSeparator.size() +
      std::max<size_t>(static_cast<unsigned long>(textFieldWidth_),
                       text_.size()));
}

int bane::LineEdit::preferredHeight() const noexcept { return 1; }

void bane::LineEdit::setLabel(std::string label) { label_ = std::move(label); }

void bane::LineEdit::setText(std::string text) { text_ = std::move(text); }

void bane::LineEdit::setTextFieldWidth(size_t width) {
  textFieldWidth_ = width;
}

void bane::LineEdit::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::doRender " << relX() << " " << relY();

  const CharPoint orig{origin()};

  // the text field must be padded to ensure the widget actually occupies the
  // entire space
  const size_t padLen{
      text_.size() >= textFieldWidth_ ? 0 : textFieldWidth_ - text_.size() + 1};
  const std::string paddedText{text_ + std::string(padLen, ' ')};
  mvaddstr(orig.y, orig.x, (label_ + labelSeparator + paddedText).c_str());
  BOOST_LOG_TRIVIAL(trace) << "#### positioning " << cursorPos_;
  positionCursorInText(cursorPos_);
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

/// Position cursor in text field
/// \param x widget coordinate
void bane::LineEdit::positionCursorInWidget(size_t x) {
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::positionCursor " << x << " cursor pos "
                           << cursorPos_;
  size_t textOffset{textStartOffset()};
  if (x < textOffset) {
    // If label was clicked, move cursor to first character position
    positionCursorInText(0);
  } else {
    positionCursorInText(x - textOffset);
  }
}

/// \param x cursor position with respect to text field (not counting label)
void bane::LineEdit::positionCursorInText(size_t x) {
  BOOST_LOG_TRIVIAL(trace) << "positionCursorInText: " << x << " of "
                           << textFieldWidth_;
  if (x < textFieldWidth_ - 1) {
    move(absY(),
         absX() + static_cast<int>(textStartOffset()) + static_cast<int>(x));
    cursorPos_ = x;
  }
}

void bane::LineEdit::handleTextKey(int c) {
  if (cursorPos_ < textFieldWidth_ - 2 && text_.size() <= textFieldWidth_) {
    text_.insert(std::min(cursorPos_, text_.size()), 1, static_cast<char>(c));
    positionCursorInText(cursorPos_ + 1);
    doRender();
  }
}

void bane::LineEdit::handleSpecialKey(SpecialKey key) {
  switch (key) {
  case SpecialKey::arrowLeft:
    positionCursorInText(cursorPos_ - 1);
    break;
  case SpecialKey::arrowRight:
    positionCursorInText(cursorPos_ + 1);
    break;
  case SpecialKey::home:
    positionCursorInText(0);
    break;
  case SpecialKey::end:
    positionCursorInText(text_.empty() ? 0 : text_.size());
    break;
  case SpecialKey::backspace:
    handleBackSpace();
    break;
  case SpecialKey::delete_:
    handleDelete();
    break;
  case SpecialKey::arrowUp:
  case SpecialKey::arrowDown:
  case SpecialKey::tab:
    break;
  };
  doRender();
}

void bane::LineEdit::handleBackSpace() {
  if (text_.empty() || cursorPos_ == 0) {
    return;
  }
  text_.erase(cursorPos_ - 1, 1);
  positionCursorInText(cursorPos_ - 1);
}

void bane::LineEdit::handleDelete() {
  if (text_.empty() || cursorPos_ >= text_.size()) {
    return;
  }
  text_.erase(cursorPos_, 1);
}
