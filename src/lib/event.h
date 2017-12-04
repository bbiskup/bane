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
