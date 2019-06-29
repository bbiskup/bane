#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "app.h"

namespace bane {

class Event;
class DummyEvent;
class ResizeEvent;
class MouseEvent;
class KeyEvent;
class CustomEvent;

/// Handler for application event.
/// Uses double dispatch (visitor pattern)
///
/// Handler functions must be invoked in the GUI thread.
class EventHandler {
public:
  explicit EventHandler(App& app);
  void handle(const ResizeEvent& e);
  void handle(const DummyEvent& e);
  void handle(const MouseEvent& e);
  void handle(const KeyEvent& e);
  void handle(const CustomEvent& e);
  void handle(const Event& e);

private:
  App& app_;
};

}; // namespace bane

#endif /* EVENT_HANDLER_H */
