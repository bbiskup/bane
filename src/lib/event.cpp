#include "event.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <boost/core/demangle.hpp>
#include <ncurses.h>

std::string bane::Event::name() const{
    return boost::core::demangle(typeid(*this).name());
}

