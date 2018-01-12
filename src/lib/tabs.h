#ifndef TABS_H
#define TABS_H

#include "widget.h"
#include "tab.h"

#include <string>

namespace bane {

// Tab widget - multiple child widgets can be selected via a
// tab bar. Only one child widget is visible at a time
class Tabs : public Widget {
public:
  Tabs(Widget* root);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;
  Tab* addTab(std::wstring name);
  size_t numTabs() const { return handlesPane_->numChildren();}
  void selectTab(size_t tabIndex);

protected:
  Widget* handlesPane_;
};
} // namespace bane

#endif /* TABS_H */
