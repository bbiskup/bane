#ifndef TAB_H
#define TAB_H

#include "widget.h"

#include <string>

namespace bane {

// Tab widget - multiple child widgets can be selected via a
// tab bar. Only one child widget is visible at a time
class Tab : public Widget {
public:
  Tab(Widget* root);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

protected:
  void onAddChild(Widget& widget) override;
};
} // namespace bane



#endif /* TAB_H */
