#include "event/event_handler.h"
#include "event/custom_event.h"
#include "event/dummy_event.h"
#include "event/event.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/resize_event.h"
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

  Widget* widget = app_.termWindow()->widgetAt(e.x, e.y);
  if (widget) {
    BOOST_LOG_TRIVIAL(trace) << "########## Event for widget: " << *widget;
    if (e.button == mouse::Button::none && app_.blushWidget() != widget) {
      app_.blush(widget);
    }

    if (e.wasClicked()) {
      app_.requestFocus(widget);
    }

    // For now, don't dispatch mouse move events to avoid
    // excessive processing and rendering
    if (e.clickType != mouse::ClickType::none) {
      widget->mouse(e);
    }
  } else {
    BOOST_LOG_TRIVIAL(trace) << "No widget at position " << e.x << ", " << e.y;
  }
}

void bane::EventHandler::handle(const KeyEvent& e) {
  BOOST_LOG_TRIVIAL(trace) << "Handling key event " << e.c;

  Widget* widget = app_.termWindow()->widgetAt(e.x, e.y);
  if (widget) {
    BOOST_LOG_TRIVIAL(trace) << "Widget: " << *widget;
    widget->key(e);
  } else {
    BOOST_LOG_TRIVIAL(trace) << "No widget at position " << e.x << ", " << e.y;
  }
}

void bane::EventHandler::handle(const CustomEvent& e) {
  BOOST_LOG_TRIVIAL(trace) << "Handling custom event ";
  e.code(app_);
}

/// Catch-all
void bane::EventHandler::handle(const Event& e) {
  BOOST_LOG_TRIVIAL(trace) << "Unsupported event type " + e.name();
}
