#include "event_handler.h"
#include "event.h"

#include <stdexcept>

bane::EventHandler::EventHandler(App& app) : app_{app} {}

void bane::EventHandler::handle(const ResizeEvent&) {
  app_.handleResize();
}

/// Catch-all
void bane::EventHandler::handle(const Event& e) {
  throw std::runtime_error{"Unsupported event type " + e.name()};
}
