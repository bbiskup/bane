#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "stateful_button.h"

namespace bane {
class RadioButton : public StatefulButton {
public:
  RadioButton(Widget* root, std::string label, bool isSelected = false);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  std::string label_;
};
} // namespace bane

#endif /* RADIO_BUTTON_H */
