#ifndef APP_H
#define APP_H

#include "event.h"
#include "pane.h"
#include "term_window.h"
#include "theme.h"
#include <mutex>
#include <queue>
#include <string>

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

  TermWindow& termWindow() { return termWindow_; }
  const Theme& theme() const { return *theme_; }

  Pane rootPane{};

private:
  void dispatchMouseEvent(int c);

  TermWindow termWindow_;
  std::string name_;
  std::unique_ptr<Theme> theme_;
  std::queue<std::unique_ptr<Event>> queue_;
  std::mutex queueMutex_;
};
} // namespace bane

#endif /* APP_H */
