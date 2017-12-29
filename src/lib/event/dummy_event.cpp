#include "event/dummy_event.h"
#include "event/event_handler.h"

void bane::DummyEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}
