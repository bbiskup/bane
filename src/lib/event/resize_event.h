#ifndef RESIZE_EVENT_H
#define RESIZE_EVENT_H

#include "event/event.h"

namespace bane {

class EventHandler;

//// Window resize
class ResizeEvent : public Event {
public:
  ResizeEvent() {}
  ~ResizeEvent() override = default;
  void accept(EventHandler& handler) const override;
};

} // namespace bane

#endif /* RESIZE_EVENT_H */
