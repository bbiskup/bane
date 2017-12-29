#ifndef POSITION_EVENT_H
#define POSITION_EVENT_H

#include "event/event.h"

namespace bane {

class EventHandler;

class PositionEvent : public Event {
public:
  PositionEvent(int x_, int y_) : x{x_}, y{y_} {}
  const int x;
  const int y;
};

} // namespace bane

#endif /* POSITION_EVENT_H */
