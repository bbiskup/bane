#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include "event/key_event.h"
#include "widget.h"

#include <string>

namespace bane {
class LineEdit : public Widget {
public:
  LineEdit(Widget* parent, std::wstring label, size_t textFieldWidth = 20,
           std::wstring text = L"");

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void setLabel(std::wstring label);
  void setText(std::wstring text);
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
  void handleDelete();
  std::wstring label_;
  size_t textFieldWidth_;
  std::wstring text_;
  size_t cursorPos_{0};
};
} // namespace bane

#endif /* LINE_EDIT_H */
