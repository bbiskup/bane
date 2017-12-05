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
