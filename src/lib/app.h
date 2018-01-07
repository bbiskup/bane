#ifndef APP_H
#define APP_H

#include "event/event.h"
#include "pane.h"
#include "term/term_window.h"
#include "theme.h"
#include "widget.h"
#include <memory>
#include <mutex>
#include <queue>
#include <string>

namespace bane {

/// Application
class App {
public:
  explicit App(std::wstring name, std::unique_ptr<Theme> theme,
               bool debug = false);
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
  Widget* focusWidget() const { return focusWidget_; }

  void blush(Widget* widget);
  Widget* blushWidget() const { return blushWidget_; }

  TermWindow* termWindow() { return termWindow_.get(); }
  const Theme& theme() const { return termWindow_->theme(); }

  bool isDebug() const { return debug_; }

  Pane rootPane{};

private:
  std::unique_ptr<TermWindow> termWindow_;
  std::wstring name_;
  bool debug_;
  std::queue<std::unique_ptr<Event>> queue_;
  std::mutex queueMutex_;
  Widget* focusWidget_{nullptr};
  Widget* blushWidget_{nullptr};
};
} // namespace bane

#endif /* APP_H */
