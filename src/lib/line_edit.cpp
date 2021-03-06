#include "line_edit.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "term/term_window.h"

#include <boost/log/trivial.hpp>

#include <algorithm>

namespace {
/// Separator between label and text
const std::wstring labelSeparator = L": ";
// const std::wstring eraseButton{L"\u00d7"}; // multiplication sign
// const std::wstring eraseButton{L"\u2602"}; // test
const std::wstring eraseButton{L"×"}; // test
// const std::string eraseButton = "x";
} // namespace

bane::LineEdit::LineEdit(Widget* parent, std::wstring label,
                         size_t textFieldWidth, std::wstring text)
    : Widget{parent}, label_{label},
      textFieldWidth_{textFieldWidth}, text_{text} {
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
      if (!e.ctrl && !e.altGr) {
        handleTextKey(e.c);
      }
    }
  });
}

int bane::LineEdit::preferredWidth() const noexcept {
  return static_cast<int>(
      label_.size() + labelSeparator.size() +
      std::max<size_t>(static_cast<unsigned long>(textFieldWidth_) + 1,
                       text_.size()) +
      eraseButton.size());
}

int bane::LineEdit::preferredHeight() const noexcept { return 1; }

void bane::LineEdit::setLabel(std::wstring label) { label_ = std::move(label); }

void bane::LineEdit::setText(std::wstring text) { text_ = std::move(text); }

void bane::LineEdit::setTextFieldWidth(size_t width) {
  textFieldWidth_ = width;
}

void bane::LineEdit::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::doRender " << relX() << " " << relY();
  // the text field must be padded to ensure the widget actually occupies the
  // entire space
  const size_t padLen{
      text_.size() >= textFieldWidth_ ? 0 : textFieldWidth_ - text_.size() + 1};
  const std::wstring paddedText{text_ + std::wstring(padLen, ' ')};
  termWindow_->move(origin());
  *termWindow_ << Font::normal << label_ << labelSeparator << Font::reverse
               << paddedText << Font::dim << eraseButton;
  positionCursorInText(cursorPos_);
}

void bane::LineEdit::onFocus() {
  BOOST_LOG_TRIVIAL(trace) << "LineEdit::onFocus: " << absY() << " "
                           << absX() + 1;
  termWindow_->move(absX() + static_cast<int>(textStartOffset()), absY());
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
  } else if (static_cast<int>(x) == width() - 1) {
    // eraser button
    text_ = L"";
    positionCursorInText(text_.size());
  } else if (x > textOffset + text_.size()) {
    positionCursorInText(text_.size());
  } else {
    positionCursorInText(x - textOffset);
  }
  doRender();
}

/// \param x cursor position with respect to text field (not counting label)
void bane::LineEdit::positionCursorInText(size_t x) {
  BOOST_LOG_TRIVIAL(trace) << "positionCursorInText: " << x << " of "
                           << textFieldWidth_;
  if (x < textFieldWidth_ - 1) {
    termWindow_->move(absX() + static_cast<int>(textStartOffset()) +
                          static_cast<int>(x),
                      absY());
    cursorPos_ = x;
  }
}

void bane::LineEdit::handleTextKey(int c) {
  if (c == '\n' || c == '\t') {
    return;
  }
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
    yieldFocus(FocusYieldHint::start);
    return;
  case SpecialKey::arrowDown:
  case SpecialKey::enter:
  case SpecialKey::tab:
    yieldFocus(FocusYieldHint::end);
    return;
  }
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
