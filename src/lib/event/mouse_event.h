#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "event/position_event.h"

namespace bane {

class EventHandler;

namespace mouse {
enum class Button { left, middle, right, notImplemented };

enum class ClickType { single, double_, release, notImplemented };
} // namespace mouse

/// allow enum class map keys
struct EnumClassHash {
  template <typename T> std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

class MouseEvent : public PositionEvent {
public:
  MouseEvent(int c);
  ~MouseEvent() override = default;
  void accept(EventHandler& handler) const override;

  mouse::Button button;
  mouse::ClickType clickType;
};

} // namespace bane

#endif /* MOUSE_EVENT_H */
