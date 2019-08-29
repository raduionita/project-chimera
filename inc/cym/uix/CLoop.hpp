#ifndef __cym_uix_cloop_hpp__
#define __cym_uix_cloop_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CLoop {
    protected:
      int64_t mStart   = {std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()}; 
      bool    mRunning = {false};
    public:
      CLoop();
      virtual ~CLoop();
    public:
      virtual int exec(int = 0);
      virtual int quit(int = 0);
    public:
      virtual bool onInit();
      virtual bool onTick();
      virtual bool onExit();
  };
}}

#endif //__cym_uix_cloop_hpp__

// @todo: CEventLoop
// @todo: CGameLoop
