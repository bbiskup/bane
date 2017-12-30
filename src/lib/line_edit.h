#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include "widget.h"

#include <string>

namespace bane {
class LineEdit : public Widget {
public:
  LineEdit(Widget* root, std::string label, int textFieldWidth = 20,
           std::string text = "");

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void setLabel(std::string label);
  void setText(std::string text);
  void setTextFieldWidth(int width);
  void doRender() override;

  bool acceptsFocus() const override { return true; }
  bool showCursorWhenFocus() const override { return true; }
  void onFocus() override;
  void onBlur() override;

private:
  unsigned long textStartOffset() const;
  std::string label_;
  int textFieldWidth_;
  std::string text_;
};
} // namespace bane

#endif /* LINE_EDIT_H */
