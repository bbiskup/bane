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

namespace mouse {
enum class Button { left, middle, right };

enum class ClickType { single, double_ };
} // namespace mouse

/// allow enum class map keys
struct EnumClassHash {
  template <typename T> std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

class MouseEvent : public Event {
public:
  MouseEvent(int x, int y, mouse::Button button, mouse::ClickType clickType);
  ~MouseEvent() override = default;
  void accept(EventHandler& handler) const override;

  const int x;
  const int y;
  const mouse::Button button;
  const mouse::ClickType clickType;
};

/*class MouseEvent() {
public:
  void handle(Widget * widget) override;
};*/

} // namespace bane

#endif /* EVENT_H */
