#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

namespace bane {
class Button : public Widget {

public:
  using Widget::Widget;

  void onFocus() override;
  void onBlur() override;
};
} // namespace bane

#endif /* BUTTON_H */
