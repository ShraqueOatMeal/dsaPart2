#include "local_time.h"
#include <ctime>
#include <iomanip>
#include <sstream>

local_time::local_time() {
  // Constructor implementation
}

local_time::~local_time() {
  // Destructor implementation
}

std::string const local_time::currentTimestamp() {
//   std::time_t now = std::time(nullptr);
//   std::tm t;
// #if defined(_WIN32)
//   localtime_s(&t, &now);
// #else
//   localtime_r(&now, &t);
// #endif
//   std::ostringstream ss;
//   ss << std::put_time(&t, "%Y-%m-%d %H:%M");
//   return ss.str();
}
