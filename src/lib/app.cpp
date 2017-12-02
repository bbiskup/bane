#include "app.h"

#include <boost/log/trivial.hpp>

bane::App::App(std::string name) : name_{std::move(name)}{}

bane::App::~App() { BOOST_LOG_TRIVIAL(trace) << "Terminating application " << name_; }

/// Run application - start processing events, until explicit termination
void bane::App::run(){
}
