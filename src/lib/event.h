#ifndef EVENT_H
#define EVENT_H

#include "widget.h"

namespace bane {

/// base class for application events
class Event {
public:
  virtual ~Event() {}
  virtual void handle(Widget* widget) = 0;
};

/// Placeholder event for testing
class DummyEvent : public Event {
public:
  DummyEvent() {}
  ~DummyEvent() override {}
  void handle(Widget* widget) override;
};

//
class ResizeEvent : public Event {
public:
  ResizeEvent() {}
  ~ResizeEvent() override {}
  void handle(Widget* widget) override;
};

/*class MouseEvent() {
public:
  void handle(Widget * widget) override;
};*/

} // namespace bane

#endif /* EVENT_H */
