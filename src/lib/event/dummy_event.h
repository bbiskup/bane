#ifndef DUMMY_EVENT_H
#define DUMMY_EVENT_H

#include "event/event.h"

#include <string>

namespace bane {

class EventHandler;

/// Placeholder event for testing
class DummyEvent : public Event {
public:
  DummyEvent() {}
  ~DummyEvent() override = default;
  void accept(EventHandler& handler) const override;
};

} // namespace bane

#endif /* DUMMY_EVENT_H */
