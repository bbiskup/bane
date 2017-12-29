#ifndef POSITION_EVENT_H
#define POSITION_EVENT_H

#include "event/event.h"

namespace bane {

class EventHandler;

class PositionEvent : public Event {
public:
  int x{-1};
  int y{-1};
};

} // namespace bane

#endif /* POSITION_EVENT_H */
