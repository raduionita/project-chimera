#include "cym/uix/CConsole.hpp"
#include "cym/uix/CApplication.hpp"

namespace cym { namespace uix {
  CConsole::CConsole(CApplication* pApp, int nCmdShow/*=0*/) : mApp{pApp} {
    log::nfo << "uix::CConsole::CConsole(CApplication*)::" << this << log::end;
    init();
  }
  
  CConsole::~CConsole() {
    log::nfo << "uix::CConsole::CConsole()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CConsole::init() {
    log::nfo << "uix::CConsole::init()::" << this << log::end;
    
    if (!::SetConsoleCtrlHandler(CConsole::ctrl, TRUE)) {
      log::nfo << "[CConsole] ::SetConsoleCtrlHandler() failed!" << log::end;
      ::MessageBox(NULL, "[CConsole] ::SetConsoleCtrlHandler() failed!", "Error", MB_OK);
    }
    
    return true;
  }
  
  BOOL WINAPI CConsole::ctrl(DWORD dwSignal) {
    log::nfo << "uix::CConsole::ctrl(DWORD)" << " SIGNAL:" << dwSignal << log::end;
    
    switch (dwSignal) {
      case CTRL_C_EVENT: {
        CApplication::instance()->quit(1);
        break;
      }
      default:break;
    }
    
    return TRUE;
  }
}}
