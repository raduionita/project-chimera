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
    using namespace std::literals;
    private:
      std::string mName;
      std::chrono::time_point<std::chrono::system_clock> mStart;
      std::chrono::time_point<std::chrono::system_clock> mMark;
    public:
      // ctor
      CBenchmark(const char* zName) : mName{zName}, mStart{std::chrono::system_clock::now()}, mMark{std::chrono::system_clock::now()} { 
        // start time
        std::time_t tTime {std::chrono::system_clock::to_time_t(mStart)};
        std::cout << "[BEN][TAG] [" << mName << "] " << std::put_time(std::localtime(&tTime), "[%F %T]\n") << std::flush;
      }
      // dtor
      ~CBenchmark() {
        // stop time & report
        auto tNow {std::chrono::system_clock::now()};
        auto tElapsedStart {std::chrono::duration_cast<std::chrono::microseconds>(tNow - mStart).count()};
        auto tElapsedMark {std::chrono::duration_cast<std::chrono::microseconds>(tNow - mMark).count()};
        std::time_t tTime {std::chrono::system_clock::to_time_t(tNow)};
        std::cout << "[BEN][END] [" << mName << "] " << std::put_time(std::localtime(&tTime), "[%F %T][+") << tElapsedMark << "µs][+" << tElapsedStart << "µs]\n";
      }
    public:
      void mark() {
        auto tNow {std::chrono::system_clock::now()};
        auto tElapsedStart {std::chrono::duration_cast<std::chrono::microseconds>(tNow - mStart).count()};
        auto tElapsedMark {std::chrono::duration_cast<std::chrono::microseconds>(tNow - mMark).count()};
        mMark = tNow;
        std::time_t tTime {std::chrono::system_clock::to_time_t(tNow)};
        std::cout << "[BEN][MRK] [" << mName << "] " << std::put_time(std::localtime(&tTime), "[%F %T][+") << tElapsedMark << "µs][+" << tElapsedStart << "µs]\n";
      }
  }; 
} // namespace sys

#define BENTAG(tag) sys::CBenchmark BENINS(tag);
#define BENMRK(tag) BENINS.mark();

#endif //BENCHMARK

#endif //__sys_cbenchmark_hpp__ 