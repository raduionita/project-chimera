#ifndef __uix_cconsole_hpp__
#define __uix_cconsole_hpp__

#include "uix/CObject.hpp"

namespace uix {
  class CConsole : public CObject {
    protected:
      CApplication* mApp = {nullptr};
    public:
      CConsole(CApplication*,int=0);
      ~CConsole();
    protected:
      virtual bool init();
    protected:
      static BOOL WINAPI ctrl(DWORD);
  };
}



#endif //__uix_cconsole_hpp__
