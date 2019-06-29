#ifndef EVENT_H
#define EVENT_H

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

} // namespace bane

#endif /* EVENT_H */
