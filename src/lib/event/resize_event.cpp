#include "event/resize_event.h"
#include "event/event_handler.h"

void bane::ResizeEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}
