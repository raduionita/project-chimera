#ifndef __sys_cthreader_hpp__
#define __sys_cthreader_hpp__

#include "sys/sys.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

#include <thread>
#include <atomic>

namespace sys {
  enum EAsync {
    NONE  = 0,
    LAZY  = 1, // not right now, let the parent function continue, MAIN + LAZY => task will execute later
    SPAWN = 2 | LAZY,
    MAIN  = 4, 
  };
    
  class CThreader : public TSingleton<CThreader> {
    public:
      void queue(std::function<void()>&& task) {
        
      }
  };
  
  inline bool async(std::function<void()>&& task, int hints = EAsync::SPAWN) {
    static const auto pThreader = CThreader::getSingleton();
    // @todo: forward task to threader
    task();
    
    return true; // true|false did it execute now? true = yes (main thread) 
  }
  
  inline bool spawn(std::function<void()>&& task) { return async(std::move(task), EAsync::SPAWN); }
}

#endif //__sys_cthreader_hpp__
