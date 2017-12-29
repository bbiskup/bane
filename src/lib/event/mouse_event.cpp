#include "event/mouse_event.h"
#include "event/event_handler.h"

#include <ncurses.h>


bane::MouseEvent::MouseEvent(int x, int y, mouse::Button button_,
                             mouse::ClickType clickType_)
    : PositionEvent{x, y}, button{button_}, clickType{clickType_} {}

void bane::MouseEvent::accept(EventHandler& handler) const {
  handler.handle(*this);
}

