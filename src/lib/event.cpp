#include "event.h"
#include "widget.h"
#include <boost/log/trivial.hpp>
#include <ncurses.h>

void bane::DummyEvent::handle(Widget*) {
  BOOST_LOG_TRIVIAL(trace) << "DummyEvent::handle";
}

void bane::ResizeEvent::handle(Widget* widget) {
  BOOST_LOG_TRIVIAL(trace) << "ResizeEvent::handle";
  clear();
  refresh();
  widget->root()->render();
}
