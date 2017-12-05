#ifndef EVENT_H
#define EVENT_H

#include "widget.h"

#include <string>

namespace bane {

/// Events may be created in any thread, bust
/// must be handled in the GUI thread

/// base class for application events
class Event {
public:
  virtual ~Event() {}
  std::string name() const;
};

/// Placeholder event for testing
class DummyEvent : public Event {
public:
  DummyEvent() {}
  ~DummyEvent() override = default;
};

//
class ResizeEvent : public Event {
public:
  ResizeEvent() {}
  ~ResizeEvent() override = default;
};

/*class MouseEvent() {
public:
  void handle(Widget * widget) override;
};*/

} // namespace bane

#endif /* EVENT_H */
