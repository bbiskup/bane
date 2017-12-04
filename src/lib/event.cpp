#include "event.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <boost/core/demangle.hpp>
#include <ncurses.h>

std::string bane::Event::name() const{
    return boost::core::demangle(typeid(*this).name());
}

void bane::DummyEvent::handle(Widget*) {
  BOOST_LOG_TRIVIAL(trace) << "DummyEvent::handle";
}

void bane::ResizeEvent::handle(Widget* widget) {
  BOOST_LOG_TRIVIAL(trace) << "ResizeEvent::handle";
  clear();
  refresh();
  widget->root()->render();
}
