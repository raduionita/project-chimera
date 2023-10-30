#ifndef __sys_csemaphore_hpp__
#define __sys_csemaphore_hpp__

#include "sys/sys.hpp"

#include <mutex>
#include <condition_variable>

namespace sys {
  class CSemaphore {
    private:
      int                     mCount;
      std::mutex              mMutex;
      std::condition_variable mCV;
    public:
      explicit CSemaphore(int nCount) {
        mCount = nCount;
        // init mutex
        // init cv
      }
    public:
      // wait
      void take() {
        std::unique_lock<std::mutex> ulk(mMutex);
        // put thread to sleap until mCount is 0
        while (mCount == 0) {
          mCV.wait(ulk, []{ });
          --mCount;
          ulk.unlock();
        }
      }

      // free
      void give() {
        std::unique_lock<std::mutex> ulk(mMutex);
        ++mCount;
        // if count was 0 before inc. => wake up a waiting thread
        if (mCount == 1) {
          mCV.notify_one();
        }
        ulk.unlock();
      }
  };

  using sem = sys::CSemaphore;
} // namespace sys

//// usage
// CQueue   gQueue;
// sys::sem gSemUsed{0};
// sys::sem gSemUsed{1};
//
// void* Producer(void*) {
//   // keep producer running forever
//   while (true) {
//     // produce item
//     CItem item = produceItem();
//     // dec. free count (wait until there's room)
//     gSemFree.take();
//
//     gQueue.addItem(item);
//
//     // incremet used count (notify consumer that there's data)
//     gSemUsed.give();
//   }
//   return nullptr;
// }
//
// void* Consumer(void*) {
//   // keep consumer forever
//   while (true) {
//     // dec. the used count (wait for data to be ready)
//     gSemUsed.wait();
//
//     CItem item = gQueue.popItem();
//
//     // inc. free count (notify producer that thare's room)
//     gSemFree.give();
//
//     // consume item
//     consumeItem(item);
//   }
//   return nullptr;
// }

#endif // __sys_csemaphore_hpp__