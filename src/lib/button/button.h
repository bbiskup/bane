#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

#include <memory>
#include <string>

namespace bane {
class Button : public Widget {
public:
  Button(Widget* root, std::string label);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;



private:
  std::string label_;
  bool isPressed_{false};
};
} // namespace bane

#endif /* BUTTON_H */
