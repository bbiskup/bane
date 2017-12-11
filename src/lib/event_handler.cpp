#include "event_handler.h"
#include "event.h"
#include "widget.h"

#include <boost/log/trivial.hpp>
#include <stdexcept>
#include <unordered_map>

bane::EventHandler::EventHandler(App& app) : app_{app} {}

void bane::EventHandler::handle(const ResizeEvent&) {
  BOOST_LOG_TRIVIAL(trace) << "EventHandler::handle";
  app_.handleResize();
}

void bane::EventHandler::handle(const DummyEvent& e) {
  BOOST_LOG_TRIVIAL(trace) << "Handling Dummy-event " + e.name();
}

void bane::EventHandler::handle(const MouseEvent& e) {
  static std::unordered_map<bane::mouse::ClickType, std::string,
                            bane::EnumClassHash>
      clickTypeStrs{{bane::mouse::ClickType::single, "single"},
                    {bane::mouse::ClickType::double_, "double"}};
  BOOST_LOG_TRIVIAL(trace) << "Handling mouse event " << e.name() << " "
                           << clickTypeStrs[e.clickType];

  Widget* widget = app_.termWindow().widgetAt(e.x, e.y);
  if (widget) {
    BOOST_LOG_TRIVIAL(trace) << "Widget: " << *widget;
    switch (e.clickType) {
    case bane::mouse::ClickType::single:
      widget->click(e.x, e.y);
      break;
    case bane::mouse::ClickType::release:
      widget->releaseMouse();
      break;
    case bane::mouse::ClickType::double_:
      BOOST_LOG_TRIVIAL(trace) << "unhandled mouse event";
    };
  } else {
    BOOST_LOG_TRIVIAL(trace) << "No widget at position " << e.x << ", " << e.y;
  }
}

/// Catch-all
void bane::EventHandler::handle(const Event& e) {
  BOOST_LOG_TRIVIAL(trace) << "Unsupported event type " + e.name();
}
