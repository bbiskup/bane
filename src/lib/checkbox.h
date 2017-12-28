#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "button.h"

namespace bane {
class CheckBox : public Button {
public:
  CheckBox(Widget* root, std::string label, bool isChecked = false);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  std::string label_;
  bool isChecked_{false};
};
} // namespace bane

#endif /* CHECKBOX_H */
