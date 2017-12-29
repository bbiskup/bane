#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "event/position_event.h"

namespace bane {

class EventHandler;

namespace mouse {
enum class Button { left, middle, right };

enum class ClickType { single, double_, release };
} // namespace mouse

/// allow enum class map keys
struct EnumClassHash {
  template <typename T> std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

class MouseEvent : public PositionEvent {
public:
  MouseEvent(int x, int y, mouse::Button button, mouse::ClickType clickType);
  ~MouseEvent() override = default;
  void accept(EventHandler& handler) const override;

  const mouse::Button button;
  const mouse::ClickType clickType;
};

} // namespace bane

#endif /* MOUSE_EVENT_H */
