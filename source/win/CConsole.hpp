#ifndef __win_cconsole_hpp__
#define __win_cconsole_hpp__

#ifdef PLATFORM_WINDOWS

#include "win/CWindow.hpp"

namespace win {
  class CConsole : public win::CWindow {
      friend class win::CApplication;
      friend class win::TApplication<CConsole>;
      using super = win::CWindow;
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
} // namespace win

#endif // PLATFORM_WINDOWS

#endif //__win_cconsole_hpp__