#ifndef BUTTON_GROUP_H
#define BUTTON_GROUP_H

#include "widget.h"

namespace bane {
class Button;

/// Container for buttons
class ButtonGroup : public Widget {
public:
  ButtonGroup(Widget* root, std::string label, Orientation orientation);
  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

protected:
  void checkChild(const Widget& widget) const override;

private:
  std::string label_;
};
} // namespace bane

#endif /* BUTTON_GROUP_H */
