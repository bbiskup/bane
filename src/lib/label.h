#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

namespace bane {

class Label : public Widget {
public:
  Label(Widget* root, std::wstring label);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;
  void setText(std::wstring text);

  void doRender() override;

private:
  std::wstring label_;
};

} // namespace bane

#endif /* LABEL_H */
