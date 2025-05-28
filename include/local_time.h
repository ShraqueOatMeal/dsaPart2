#pragma once
#include <string>

class local_time {
public:
  local_time();
  ~local_time();

  std::string const static currentTimestamp();
};
