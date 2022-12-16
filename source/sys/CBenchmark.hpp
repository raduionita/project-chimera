#ifndef __sys_cbenchmark_hpp__
#define __sys_cbenchmark_hpp__

#ifndef BENCHMARK // -benchmark
#define BENTAG(tag)
#define BENMRK(tag)
#else // +benchmark

#include "sys/sys.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

namespace sys {
  class CBenchmark {
    private:
      std::string mName;
      std::chrono::time_point<std::chrono::system_clock> mStart;
    public:
      // ctor
      CBenchmark(const char* zName) : mName{zName}, mStart{std::chrono::system_clock::now()} { 
        // start time
        std::time_t tTime {std::chrono::system_clock::to_time_t(mStart)};
        std::cout << "[BEN][TAG] [" << mName << "] " << std::put_time(std::localtime(&tTime), "[%F %T]\n") << std::flush;
      }
      // dtor
      ~CBenchmark() {
        // stop time & report
        using namespace std::literals;
        auto tEnd {std::chrono::system_clock::now()};
        auto tElapsed {std::chrono::duration_cast<std::chrono::microseconds>(tEnd - mStart).count()};
        std::time_t tTime {std::chrono::system_clock::to_time_t(tEnd)};
        std::cout << "[BEN][END] [" << mName << "] " << std::put_time(std::localtime(&tTime), "[%F %T][+") << tElapsed << "µs]\n";
      }
  }; 
} // namespace sys

#define BENTAG(tag) sys::CBenchmark BENINS(tag);
#define BENMRK(tag)

#endif //BENCHMARK

#endif //__sys_cbenchmark_hpp__ 