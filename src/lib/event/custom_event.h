#ifndef CUSTOM_EVENT_H
#define CUSTOM_EVENT_H

#include "event/event.h"
#include "app.h"

#include <string>
#include <functional>

namespace bane {

class EventHandler;

/// CustomEvent allows execution of code on the UI thread
class CustomEvent : public Event {
public:
  using CodeT = std::function<void(App& app)>;
  CustomEvent(CodeT code_) : code{code_} {}
  ~CustomEvent() override = default;
  void accept(EventHandler& handler) const override;
  CodeT code;
};

} // namespace bane

#endif /* CUSTOM_EVENT_H */
