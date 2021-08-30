#ifndef __sys_ctask_hpp__
#define __sys_ctask_hpp__

#include "sys/sys.hpp"
#include "sys/TSingleton.hpp"
#include "sys/CException.hpp"

#include <thread>
#include <future>
#include <atomic>
#include <queue>

namespace sys {
  class CTask;        typedef sys::ptr<CTask> PTask;
  class CTaskManager;
  
  enum ETask {
    NONE  = 0,
    LAZY  = 1, // not right now, let the parent function continue, MAIN + LAZY => task will execute later
    SPAWN = 2 | LAZY,
    ASYNC = SPAWN,
    MAIN  = 4, 
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTask {
    protected:
      std::future<void>     mFuture;
      std::function<void()> mDone;
    public:
      inline CTask(std::function<void()>&& fFunc, std::function<void()>&& fDone) : mDone{std::move(fDone)} {
        
        mFuture = std::async(std::launch::async, fFunc);
        
      }
      virtual ~CTask() = default;
    public:
      inline void done() {  }
    public:
      inline bool isDone() const { return mFuture.valid(); } 
  };
    
  class CTaskManager : public TSingleton<CTaskManager> {
      friend class CTask;
      friend class TSingleton<CTaskManager>;
    protected:
      std::queue<PTask> mTasks;
      bool              mLoaded {false};
    protected:
      inline CTaskManager() { SYS_LOG_NFO("cym::CTaskManager::CTaskManager()"); }
      inline virtual ~CTaskManager() { SYS_LOG_NFO("cym::CTaskManager::~CTaskManager()"); }
    public:
      // static void task(std::function<void()>&& task) {}
      
// @TODO check if CTaskManager has been called, if not throw error (if more waiting task than system threads)
      
// @TODO check available threads on load (if not threads, everything should run on main) 
      inline static void boot() { CTaskManager::getSingleton().mLoaded = true; }
      /* CTaskManager::sync() // check what is done end execute code for main thread */
      inline static void sync() { 
        static auto& self {CTaskManager::getSingleton()};
        if (self.mLoaded) {
          while (!self.mTasks.empty()) {
            auto& pTask {self.mTasks.back()};
            if (!pTask->isDone()) {
              break;
            }
            // ex: after texture loader call ogl stuff in notify only on the main thread 
            pTask->done();
            self.mTasks.pop();
          }
        }
      }
      
// @TODO if hints == ETask::MAIN => start task but execute it on CTaskManager::join() 
      
      /* CTaskManager::task(function,function,ETask::ASYNC) // run task on another thread */
      inline static void task(std::function<void()>&& fFunc, std::function<void()>&& fDone, int hints = ETask::ASYNC) {
        static auto& self {CTaskManager::getSingleton()};
        // if loaded: run threaded else: run now  
        if ((self.mLoaded) && (hints & ETask::ASYNC)) {
          // start it on a new thread
          self.mTasks.push(PTask{new CTask{std::move(fFunc),std::move(fDone)}});
          // ? return true; // true|false did it execute now? true = yes (main thread) 
        } else {
          // execute here (func & done)
          if (fFunc) { 
            fFunc(); 
          }
          if (fDone) { 
            fDone(); 
          }
        }
      }
  };
  
// @TODO when runnung done() on main thread, benchmark time, and if it one takes too long, don't execute the next (this frame)
  
  inline void task(std::function<void()>&& fFunc, std::function<void()>&& fDone, int hints = ETask::ASYNC) {
    CTaskManager::task(std::move(fFunc), std::move(fDone), hints);
  }
  
  inline void task(std::function<void()>&& fFunc, int hints = ETask::ASYNC) {
    CTaskManager::task(std::move(fFunc), nullptr, hints);
  }
  
  inline void sync() { CTaskManager::sync(); }
}

#endif //__sys_ctask_hpp__
