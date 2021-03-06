#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

namespace bane {
class StatefulButton : public Widget {

public:
  using Widget::Widget;
  StatefulButton(Widget* parent, std::wstring label, bool state = false);

  void toggleState();
  void setState(bool state = true);
  virtual void pick() = 0;

  bool acceptsFocus() const override { return true; }
  bool showCursorWhenFocus() const override { return true; }
  void onFocus() override;
  void onBlur() override;

protected:
  std::wstring label_;
  bool state_{false};
};
} // namespace bane

#endif /* BUTTON_H */
