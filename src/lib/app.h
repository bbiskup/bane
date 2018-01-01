#ifndef APP_H
#define APP_H

#include "event/event.h"
#include "pane.h"
#include "term/term_window.h"
#include "widget.h"
#include "theme.h"
#include <mutex>
#include <queue>
#include <string>
#include <memory>

namespace bane {

/// Application 
class App {
public:
  explicit App(std::string name, std::unique_ptr<Theme> theme);
  ~App();
  App(const App&) = delete;
  App(App&&) = delete;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = delete;

  [[noreturn]] void run();

  template <typename EventT, typename... Args> void postEvent(Args&&... args) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    queue_.push(std::unique_ptr<Event>(new EventT(args...)));
  }

  void render();
  void handleResize();

  void requestFocus(Widget* widget);
  void yieldFocus(Widget* widget, FocusYieldHint yieldHint);

  TermWindow* termWindow() { return termWindow_.get(); }
  const Theme& theme() const { return termWindow_->theme(); }

  Pane rootPane{};
  Widget* focusWidget() const{return focusWidget_;}

private:
  std::unique_ptr<TermWindow> termWindow_;
  std::string name_;
  std::queue<std::unique_ptr<Event>> queue_;
  std::mutex queueMutex_;
  Widget* focusWidget_{nullptr};
};
} // namespace bane

#endif /* APP_H */
