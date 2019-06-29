#ifndef TAB_H
#define TAB_H

#include "widget.h"

namespace bane {
class Tab : public Widget {

public:
  using Widget::Widget;
  Tab(Widget* parent, std::wstring label);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

protected:
  std::wstring label_;
};
} // namespace bane

#endif /* TAB_H */
