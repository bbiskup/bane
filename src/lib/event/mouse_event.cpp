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
  if (getmouse(&mort) == OK) {
    x = mort.x;
    y = mort.y;
    BOOST_LOG_TRIVIAL(trace)
        << "MouseEvent: " << x << ", " << y << ": bstate " << mort.bstate;
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
  BOOST_LOG_TRIVIAL(trace) << "Constructed mouse event: " << *this;
}

void bane::MouseEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}

/// \return true, if any button was clicked
bool bane::MouseEvent::wasClicked() const {
  // TODO support triple click?
  return (clickType == mouse::ClickType::single ||
          clickType == mouse::ClickType::double_);
}

std::ostream& bane::operator<<(std::ostream& strm, const MouseEvent& e) {
  std::string buttonStr;
  switch (e.button) {
  case mouse::Button::left:
    buttonStr = "left";
    break;
  case mouse::Button::middle:
    buttonStr = "middle";
    break;
  case mouse::Button::right:
    buttonStr = "right";
    break;
  case mouse::Button::none:
    buttonStr = "none";
    break;
  case mouse::Button::notImplemented:
    buttonStr = "notImplemented";
    break;
  }

  std::string clickTypeStr;
  switch (e.clickType) {
  case mouse::ClickType::single:
    clickTypeStr = "single";
    break;
  case mouse::ClickType::double_:
    clickTypeStr = "double";
    break;
  case mouse::ClickType::release:
    clickTypeStr = "release";
    break;
  case mouse::ClickType::none:
    clickTypeStr = "none";
    break;
  case mouse::ClickType::notImplemented:
    clickTypeStr = "notImplemented";
    break;
  }

  strm << "MouseEvent button=" << buttonStr << " clickType=" << clickTypeStr;
  return strm;
}
