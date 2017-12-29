#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

namespace bane {
class StatefulButton : public Widget {

public:
  using Widget::Widget;

  bool acceptsFocus() const override { return true; }
  bool showCursorWhenFocus() const override { return true; }
  void onFocus() override;
  void onBlur() override;
};
} // namespace bane

#endif /* BUTTON_H */
