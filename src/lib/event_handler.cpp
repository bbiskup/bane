#include "event_handler.h"
#include "event.h"

#include <boost/log/trivial.hpp>
#include <stdexcept>

bane::EventHandler::EventHandler(App& app) : app_{app} {}

void bane::EventHandler::handle(const ResizeEvent&) {
  BOOST_LOG_TRIVIAL(trace) << "EventHandler::handle";
  app_.handleResize();
}

/// Catch-all
void bane::EventHandler::handle(const Event& e) {
  // throw std::runtime_error{"Unsupported event type " + e.name()};
  BOOST_LOG_TRIVIAL(trace) << "Unsupported event type " + e.name();
}
