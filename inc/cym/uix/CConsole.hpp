#ifndef __cym_uix_cconsole_hpp__
#define __cym_uix_cconsole_hpp__

#include "CObject.hpp"

namespace cym::uix {
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



#endif //__cym_uix_cconsole_hpp__
