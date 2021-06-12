#ifndef __sys_ctimer_hpp__
#define __sys_ctimer_hpp__

#include "sys/sys.hpp"

#include <chrono>

namespace sys { 
  class CTimer {
    public:
      typedef std::chrono::milliseconds milli;
      typedef std::chrono::milliseconds milliseconds;
      typedef std::chrono::seconds      secs;
      typedef std::chrono::seconds      seconds;
    protected:
      std::chrono::time_point<std::chrono::system_clock> mStart;
      bool                                               mRunning {false};
    public:
      inline CTimer(bool bRunning = false) : mRunning{bRunning} { if (mRunning) mStart = std::chrono::system_clock::now(); };
    public:
      inline static CTimer start() { return CTimer(true); }
      inline static auto now()     { return std::chrono::system_clock::now(); }
      inline void pause() { mRunning = false; }
      inline void reset() { mStart = std::chrono::system_clock::now(); mRunning = true; }
      inline auto elapsed() { return mRunning ? std::chrono::duration_cast<std::chrono::milliseconds>(now() - mStart).count() : (long long)(0); }
      template<typename T> inline auto elapsed() { return mRunning ? std::chrono::duration_cast<T>(now() - mStart).count() : (long long)(0); }
  };
}

#endif //__ctimer_hpp__
