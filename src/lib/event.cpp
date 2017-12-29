#include "event.h"
#include "event_handler.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <boost/core/demangle.hpp>
#include <ncurses.h>

std::string bane::Event::name() const{
    return boost::core::demangle(typeid(*this).name());
}

void bane::DummyEvent::accept(EventHandler& handler) const{
    handler.handle(*this);
}

void bane::ResizeEvent::accept(EventHandler& handler) const{
    handler.handle(*this);
}

bane::MouseEvent::MouseEvent(int x_, int y_, mouse::Button button_, mouse::ClickType clickType_): x{x_}, y{y_}, button{button_}, clickType{clickType_}{}


void bane::MouseEvent::accept(EventHandler& handler) const{
    handler.handle(*this);
}

bane::KeyEvent::KeyEvent(int c_): c{c_}{}


void bane::KeyEvent::accept(EventHandler& handler) const{
    handler.handle(*this);
}
