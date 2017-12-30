#include "event/key_event.h"
#include "event/event_handler.h"

#include <boost/algorithm/string/predicate.hpp>
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

    // 'delete character' key
    {KEY_DC, bane::SpecialKey::delete_},
};
}

bane::KeyEvent::KeyEvent(int c_) : c{c_} {
  getyx(stdscr, y, x);
  auto specialKeyIt = specialKeyMap.find(c);
  if (specialKeyIt != specialKeyMap.end()) {
    specialKey = specialKeyIt->second;
  }

  std::string keyName{keyname(c)};

  if (keyName.size() > 1 && keyName[0] == '^') {
    ctrl = true;
  }

  if (boost::starts_with(keyName, "M-")) {
    altGr = true;
  }

  BOOST_LOG_TRIVIAL(trace) << "KeyEvent: " << x << ", " << y << " " << c << " "
                           << keyname(c) << " " << (ctrl ? "CTRL" : "") << " "
                           << (altGr ? "ALT-GR" : "");
}

void bane::KeyEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}
