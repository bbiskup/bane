#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "app.h"

namespace bane {

class Event;
class ResizeEvent;


/// Handler for application event.
/// Uses double dispatch.
class EventHandler {
public:
  explicit EventHandler(App& app);
  void handle(const ResizeEvent& e);
  [[noreturn]] void handle(const Event& e);

private:
  App& app_;
};

}; // namespace bane

#endif /* EVENT_HANDLER_H */
