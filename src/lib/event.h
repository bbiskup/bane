#ifndef EVENT_H
#define EVENT_H

#include "widget.h"

#include <string>

namespace bane {

/// Events may be created in any thread, bust
/// must be handled in the GUI thread


class EventHandler;

/// base class for application events
class Event {
public:
  virtual ~Event() {}
  std::string name() const;
  
  /// Double dispatch
  virtual void accept(EventHandler& handler) const = 0;
};

/// Placeholder event for testing
class DummyEvent : public Event {
public:
  DummyEvent() {}
  ~DummyEvent() override = default;
  void accept(EventHandler& handler) const override;
};

//
class ResizeEvent : public Event {
public:
  ResizeEvent() {}
  ~ResizeEvent() override = default;
  void accept(EventHandler& handler) const override;
};

/*class MouseEvent() {
public:
  void handle(Widget * widget) override;
};*/

} // namespace bane

#endif /* EVENT_H */
