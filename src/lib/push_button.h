#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "widget.h"

#include <memory>
#include <string>

namespace bane {
class PushButton : public Widget {
public:
  PushButton(Widget* root, std::string label);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  std::string label_;
  bool isPressed_{false};
};
} // namespace bane

#endif /* PUSH_BUTTON_H */
