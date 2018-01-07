#ifndef BUTTON_GROUP_H
#define BUTTON_GROUP_H

#include "widget.h"

namespace bane {

/// Container for buttons
class ButtonGroup : public Widget {
public:
  ButtonGroup(Widget* root, std::wstring label, Orientation orientation);
  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

  bool acceptsFocus() const override { return true; }
  bool showCursorWhenFocus() const override { return true; }
  void onFocus() override;

protected:
  void onAddChild(Widget& widget) override;

private:
  std::wstring label_;
};
} // namespace bane

#endif /* BUTTON_GROUP_H */
