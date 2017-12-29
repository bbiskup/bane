#include "event/event.h"
#include <boost/core/demangle.hpp>

std::string bane::Event::name() const {
  return boost::core::demangle(typeid(*this).name());
}
