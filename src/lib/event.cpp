#include "event.h"
#include "event_handler.h"
#include "widget.h"

#include <boost/core/demangle.hpp>
#include <boost/log/trivial.hpp>
#include <ncurses.h>

#include <unordered_map>

namespace {
std::unordered_map<int, bane::SpecialKey> specialKeyMap{
    {KEY_UP, bane::SpecialKey::arrowUp},
    {KEY_RIGHT, bane::SpecialKey::arrowRight},
    {KEY_DOWN, bane::SpecialKey::arrowDown},
    {KEY_LEFT, bane::SpecialKey::arrowLeft},
};
}

std::string bane::Event::name() const {
  return boost::core::demangle(typeid(*this).name());
}

void bane::DummyEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}

void bane::ResizeEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}

bane::MouseEvent::MouseEvent(int x, int y, mouse::Button button_,
                             mouse::ClickType clickType_)
    : PositionEvent{x, y}, button{button_}, clickType{clickType_} {}

void bane::MouseEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}

bane::KeyEvent::KeyEvent(int x, int y, int c_) : PositionEvent{x, y}, c{c_} {
  auto specialKeyIt = specialKeyMap.find(c);
  if (specialKeyIt != specialKeyMap.end()) {
    specialKey = specialKeyIt->second;
  }
}

void bane::KeyEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}

