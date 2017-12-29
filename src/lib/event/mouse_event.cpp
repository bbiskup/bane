#include "event/mouse_event.h"
#include "event/event_handler.h"

#include <boost/log/trivial.hpp>
#include <ncurses.h>
#include <unordered_map>

namespace {
std::unordered_map<mmask_t,
                   std::pair<bane::mouse::Button, bane::mouse::ClickType>>
    buttonMap{{BUTTON1_CLICKED,
               {bane::mouse::Button::left, bane::mouse::ClickType::single}},
              {BUTTON1_DOUBLE_CLICKED,
               {bane::mouse::Button::left, bane::mouse::ClickType::double_}},
              {BUTTON1_RELEASED,
               {bane::mouse::Button::left, bane::mouse::ClickType::release}}};
} // namespace

/// \param c ncurses character
bane::MouseEvent::MouseEvent(int c) {
  MEVENT mort;
  getmouse(&mort);
  x = mort.x;
  y = mort.y;
  auto eventSpecIter = buttonMap.find(mort.bstate);
  if (eventSpecIter == buttonMap.end()) {
    BOOST_LOG_TRIVIAL(trace)
        << "Unsupported mouse event " << c << " " << mort.bstate;
    button = mouse::Button::notImplemented;
    clickType = mouse::ClickType::notImplemented;
  } else {
    std::tie(button, clickType) = eventSpecIter->second;
  }
}

void bane::MouseEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}
