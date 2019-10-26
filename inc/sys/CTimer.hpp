#ifndef __sys_ctimer_hpp__
#define __sys_ctimer_hpp__

#include "sys.hpp"

#include <chrono>

namespace ogl { 
  class CTimer {
    protected:
      std::chrono::steady_clock::time_point mStart;
    public:
      CTimer();
    public:
      void reset();
      uint64_t millisec();
      uint64_t microsec();
  };
}

#endif //__ctimer_hpp__
