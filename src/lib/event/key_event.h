#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "event/position_event.h"

#include <boost/optional.hpp>

namespace bane {

class EventHandler;

enum class SpecialKey {
  arrowUp,
  arrowRight,
  arrowDown,
  arrowLeft,
  home,
  end,
  backspace,
  delete_,
  tab,
  enter
};

class KeyEvent : public PositionEvent {
public:
  KeyEvent(int c);
  ~KeyEvent() override = default;
  void accept(EventHandler& handler) const override;

  const int c; // ncurses character
  const std::string keyName;
  boost::optional<SpecialKey> specialKey;
  bool ctrl{false};
  bool altGr{false};
};

} // namespace bane

#endif /* KEY_EVENT_H */
