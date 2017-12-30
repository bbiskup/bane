#include "event/key_event.h"
#include "event/event_handler.h"

#include <boost/log/trivial.hpp>
#include <ncurses.h>

#include <unordered_map>

namespace {
std::unordered_map<int, bane::SpecialKey> specialKeyMap{
    {KEY_UP, bane::SpecialKey::arrowUp},
    {KEY_RIGHT, bane::SpecialKey::arrowRight},
    {KEY_DOWN, bane::SpecialKey::arrowDown},
    {KEY_LEFT, bane::SpecialKey::arrowLeft},

    {KEY_HOME, bane::SpecialKey::home},
    {KEY_END, bane::SpecialKey::end},
    {KEY_BACKSPACE, bane::SpecialKey::backspace},
};
}

bane::KeyEvent::KeyEvent(int c_) : c{c_} {
  getyx(stdscr, y, x);
  BOOST_LOG_TRIVIAL(trace) << "KeyEvent: " << x << ", " << y;
  auto specialKeyIt = specialKeyMap.find(c);
  if (specialKeyIt != specialKeyMap.end()) {
    specialKey = specialKeyIt->second;
  }
}

void bane::KeyEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}
