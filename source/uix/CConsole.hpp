#ifndef __uix_cconsole_hpp__
#define __uix_cconsole_hpp__

#include "uix/CWindow.hpp"

namespace uix {
  class CConsole : public uix::CWindow {
      friend class uix::CApplication;
      friend class uix::TApplication<CConsole>;
      using super = uix::CWindow;
    private:
      static bool sMain; // TODO: atomic
      bool   mMain {false};
      HANDLE mInput    {INVALID_HANDLE_VALUE};
      HANDLE mOutput   {INVALID_HANDLE_VALUE};
      HANDLE mError    {INVALID_HANDLE_VALUE};
      HANDLE mOriginal {INVALID_HANDLE_VALUE};
      HANDLE mTerminate{INVALID_HANDLE_VALUE};
    public:
      CConsole();
      ~CConsole();
    protected:
      static BOOL WINAPI ctrl(DWORD);

    public:
      inline const HANDLE& getInputHandle() const  { return mInput; }
      inline const HANDLE& getOutputHandle() const { return mOutput; }
  };
} // namespace uix

#endif //__uix_cconsole_hpp__