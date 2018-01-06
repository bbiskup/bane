#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "event/position_event.h"

#include <iostream>

namespace bane {

class EventHandler;

namespace mouse {
enum class Button { left, middle, right, none, notImplemented };

enum class ClickType { single, double_, release, none, notImplemented };
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
  bool wasClicked() const;

  mouse::Button button{mouse::Button::none};
  mouse::ClickType clickType{mouse::ClickType::none};

  friend std::ostream& operator<<(std::ostream& strm, const MouseEvent& e);
};

std::ostream& operator<<(std::ostream& strm, const MouseEvent& e);

} // namespace bane

#endif /* MOUSE_EVENT_H */
