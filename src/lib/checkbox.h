#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "stateful_button.h"

namespace bane {
class CheckBox : public StatefulButton {
public:
  CheckBox(Widget* root, std::wstring label, bool isChecked = false);

  void pick() override;

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;
};
} // namespace bane

#endif /* CHECKBOX_H */
