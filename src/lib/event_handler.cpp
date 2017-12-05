#include "event_handler.h"
#include "event.h"

#include <boost/log/trivial.hpp>
#include <stdexcept>

bane::EventHandler::EventHandler(App& app) : app_{app} {}

void bane::EventHandler::handle(const ResizeEvent&) {
  BOOST_LOG_TRIVIAL(trace) << "EventHandler::handle";
  app_.handleResize();
}

void bane::EventHandler::handle(const DummyEvent& e) {
  BOOST_LOG_TRIVIAL(trace) << "Handling Dummy-event" + e.name();
}

/// Catch-all
void bane::EventHandler::handle(const Event& e) {
  BOOST_LOG_TRIVIAL(trace) << "Unsupported event type " + e.name();
}
