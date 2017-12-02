#ifndef APP_H
#define APP_H

#include "term_window.h"
#include <string>

namespace bane{
    /// Application
    class App{
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
    };
}


#endif /* APP_H */
