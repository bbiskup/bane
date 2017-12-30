#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include "widget.h"
#include "event/key_event.h"

#include <string>

namespace bane {
class LineEdit : public Widget {
public:
  LineEdit(Widget* root, std::string label, size_t textFieldWidth = 20,
           std::string text = "");

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void setLabel(std::string label);
  void setText(std::string text);
  void setTextFieldWidth(size_t width);
  void doRender() override;

  bool acceptsFocus() const override { return true; }
  bool showCursorWhenFocus() const override { return true; }
  void onFocus() override;
  void onBlur() override;

private:
  unsigned long textStartOffset() const;
  void positionCursorInWidget(size_t x);
  void positionCursorInText(size_t x);
  void handleTextKey(int c);
  void handleSpecialKey(SpecialKey key);
  void handleBackSpace();
  std::string label_;
  size_t textFieldWidth_;
  std::string text_;
  size_t cursorPos_{0};
};
} // namespace bane

#endif /* LINE_EDIT_H */
