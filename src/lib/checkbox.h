#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "stateful_button.h"

namespace bane {
class CheckBox : public StatefulButton {
public:
  CheckBox(Widget* root, std::string label, bool isChecked = false);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  std::string label_;
};
} // namespace bane

#endif /* CHECKBOX_H */
