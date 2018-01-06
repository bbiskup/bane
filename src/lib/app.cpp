#include "app.h"
#include "event/event.h"
#include "event/event_handler.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/resize_event.h"
#include "term/ncurses_term_window.h"
#include "widget.h"

#include <boost/log/trivial.hpp>
#include <ncurses.h>

#include <mutex>
#include <utility>

bane::App::App(std::string name, std::unique_ptr<Theme> theme, bool debug)
    : name_{std::move(name)}, debug_{debug} {
  termWindow_.reset(new NCursesTermWindow{std::move(theme)});
  rootPane.setApp(*this);
  rootPane.setTermWindow(termWindow_.get());
  handleResize();
  rootPane.render();
}

bane::App::~App() {
  BOOST_LOG_TRIVIAL(trace) << "Terminating application " << name_;
}

void bane::App::render() { rootPane.render(); }
void bane::App::handleResize() {
  BOOST_LOG_TRIVIAL(trace) << "App::handleResize";
  termWindow_->updateSize();
  rootPane.resize(termWindow_->width(), termWindow_->height());
  clear();
  refresh();
  rootPane.render();
}

void bane::App::requestFocus(Widget* widget) {
  if (!widget->acceptsFocus()) {
    return;
  }
  BOOST_LOG_TRIVIAL(trace) << "requesting focus for " << widget->id();
  focusWidget_ = widget;
  widget->render();
}

void bane::App::yieldFocus(Widget* widget, FocusYieldHint yieldHint) {
  if (yieldHint == FocusYieldHint::start) {
    if (widget->focusPredecessor()) {
      requestFocus(widget->focusPredecessor());
    }
  } else if (yieldHint == FocusYieldHint::end) {
    if (widget->focusSuccessor()) {
      requestFocus(widget->focusSuccessor());
    }
  }
}

void bane::App::blush(Widget* widget) {
  if (blushWidget_) {
    blushWidget_->blush(false);
  }
  blushWidget_ = widget;
  blushWidget_->blush(true);
}

/// Run application - start processing events, until explicit termination
void bane::App::run() {
  EventHandler eventHandler(*this);
  BOOST_LOG_TRIVIAL(trace) << "App::run";
  render();
  while (true) {
    int c = getch();
    // non-blocking read returns -1

    if (c == KEY_MOUSE) {
      postEvent<MouseEvent>(c);
    } else if (c != -1) {

      switch (c) {
      case KEY_RESIZE:
        postEvent<ResizeEvent>();
        break;
      default:
        postEvent<KeyEvent>(c);
        break;
      }
    }

    // Check for application events
    std::unique_lock<std::mutex> lock{queueMutex_, std::try_to_lock};
    if (lock.owns_lock()) {
      if (queue_.size()) {
        std::unique_ptr<Event> event = std::move(queue_.front());
        BOOST_LOG_TRIVIAL(trace) << "Got application event " << event->name();
        event->accept(eventHandler);
        queue_.pop();
      }
    }
  }
}
