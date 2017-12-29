#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "button.h"

namespace bane {
class RadioButton : public Button {
public:
  RadioButton(Widget* root, std::string label, bool isSelected = false);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;
  void setSelected(bool isSelected);

private:
  std::string label_;
  bool isSelected_{false};
};
} // namespace bane

#endif /* RADIO_BUTTON_H */
