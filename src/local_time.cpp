#include "local_time.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

local_time::local_time() {
  // Constructor implementation
}

local_time::~local_time() {
  // Destructor implementation
}

std::string const local_time::currentTimestamp() {
  std::time_t now = std::time(nullptr);
  std::tm t;
#if defined(_WIN32)
  // Fallback if localtime_s is unavailable
  std::tm* tmp = std::localtime(&now);
  if (tmp) t = *tmp;
#else
  localtime_r(&now, &t);
#endif
  std::ostringstream ss;
  ss << std::put_time(&t, "%d/%m/%Y %H:%M");
  return ss.str();
}
