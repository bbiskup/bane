#include "logging.h"
#include "env.h"

#include <boost/locale.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <cstdlib>

namespace logging = boost::log;

namespace {
std::string appName{"bane"};
}

inline logging::trivial::severity_level log_level_from_env() {
  const char* level_name_{getenv((appName + "_LOG_LEVEL").c_str())};
  if (level_name_ == nullptr) {
    return logging::trivial::trace;
  }
  std::string level_name{level_name_};

  logging::trivial::severity_level result;
  if (level_name == "trace") {
    result = logging::trivial::trace;
  } else if (level_name == "debug") {
    result = logging::trivial::debug;
  } else if (level_name == "info") {
    result = logging::trivial::info;
  } else if (level_name == "warning") {
    result = logging::trivial::warning;
  } else if (level_name == "error") {
    result = logging::trivial::error;
  } else if (level_name == "fatal") {
    result = logging::trivial::fatal;
  } else {
    result = logging::trivial::info;
  }
  return result;
}
void bane::initLogging() {
  auto sink = logging::add_file_log(appName + ".log");
  std::locale loc = boost::locale::generator()(bane::locale());
  sink->imbue(loc);
  sink->locked_backend()->auto_flush(true);
  logging::trivial::severity_level log_level = log_level_from_env();
  logging::core::get()->set_filter(logging::trivial::severity >= log_level);
}
