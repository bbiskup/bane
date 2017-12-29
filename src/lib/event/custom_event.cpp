#include "event/custom_event.h"
#include "event/event_handler.h"

void bane::CustomEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}
