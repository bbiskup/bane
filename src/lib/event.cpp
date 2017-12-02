#include "event.h"
#include <boost/log/trivial.hpp>
#include <ncurses.h>

void bane::DummyEvent::handle() {
  BOOST_LOG_TRIVIAL(trace) << "DummyEvent::handle";
}

void bane::ResizeEvent::handle() {
  BOOST_LOG_TRIVIAL(trace) << "ResizeEvent::handle";
  clear();
  refresh();
}
