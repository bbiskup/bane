#ifndef APP_H
#define APP_H

//#include "event_queue.h"
#include "term_window.h"
#include "event.h"
#include <boost/lockfree/queue.hpp>
#include <string>

namespace bane {
/// Application
class App {
public:
  App(std::string name);
  ~App();
  App(const App&) = delete;
  App(App&&) = delete;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = delete;

  [[noreturn]] void run();

private:
  std::string name_;
  TermWindow termWindow_{};
//  EventQueue eventQueue_;
  //boost::lockfree::queue<std::unique_ptr<Event*>> queue_;
};
} // namespace bane

#endif /* APP_H */
