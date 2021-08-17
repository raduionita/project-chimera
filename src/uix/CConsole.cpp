#include "uix/CConsole.hpp"
#include "uix/CApplication.hpp"

namespace uix {
  CConsole::CConsole(CApplication* pApp, int nCmdShow/*=0*/) : mApp{pApp} {
    SYS_LOG_NFO("uix::CConsole::CConsole(CApplication*,int)::" << this);
    init();
  }
  
  CConsole::~CConsole() {
    SYS_LOG_NFO("uix::CConsole::~CConsole()::" << this);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CConsole::init() {
    SYS_LOG_NFO("uix::CConsole::init()::" << this);
    
    if (!::SetConsoleCtrlHandler(CConsole::ctrl, TRUE)) {
      SYS_LOG_NFO("[CConsole] ::SetConsoleCtrlHandler() failed!");
      ::MessageBox(NULL, "[CConsole] ::SetConsoleCtrlHandler() failed!", "Error", MB_OK);
    }
    
    return true;
  }
  
  BOOL WINAPI CConsole::ctrl(DWORD dwSignal) {
    SYS_LOG_NFO("uix::CConsole::ctrl(DWORD)" << " SIGNAL:" << dwSignal);
    
    switch (dwSignal) {
      case CTRL_C_EVENT: {
        CApplication::instance()->quit(1);
        break;
      }
      default:break;
    }
    
    return TRUE;
  }
}
