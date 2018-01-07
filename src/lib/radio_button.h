#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "stateful_button.h"

namespace bane {
class RadioButton : public StatefulButton {
public:
  RadioButton(Widget* root, std::wstring label, bool isSelected = false);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void pick() override;

  void doRender() override;
};
} // namespace bane

#endif /* RADIO_BUTTON_H */
