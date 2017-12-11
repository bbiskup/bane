#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

#include <boost/signals2.hpp>
#include <memory>
#include <string>

namespace bane {
class Button : public Widget {
public:
  Button(Widget* root, std::string label);

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

  // Signals & slots
  using OnMouseRelease = boost::signals2::signal<void()>;
  using OnMouseReleaseSlotType = OnMouseRelease::slot_type;

  boost::signals2::connection
  doOnMouseRelease(const OnMouseReleaseSlotType& slot);

  void releaseMouse(int x, int y);

private:
  std::string label_;
};
} // namespace bane

#endif /* BUTTON_H */
