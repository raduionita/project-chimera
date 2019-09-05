#include "cym/uix/CConsole.hpp"
#include "cym/uix/CApplication.hpp"

namespace cym { namespace uix {
  CConsole::CConsole(CApplication* pApp, int nCmdShow/*=0*/) : mApp{pApp} {
    std::cout << "uix::CConsole::CConsole(CApplication*)::" << this << std::endl;
    init();
  }
  
  CConsole::~CConsole() {
    std::cout << "uix::CConsole::CConsole()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CConsole::init() {
    std::cout << "uix::CConsole::init()::" << this << std::endl;
    
    if (!::SetConsoleCtrlHandler(CConsole::ctrl, TRUE)) {
      std::cout << "[CConsole] ::SetConsoleCtrlHandler() failed!" << std::endl;
      ::MessageBox(NULL, "[CConsole] ::SetConsoleCtrlHandler() failed!", "Error", MB_OK);
    }
    
    return true;
  }
  
  BOOL WINAPI CConsole::ctrl(DWORD dwSignal) {
    std::cout << "uix::CConsole::ctrl(DWORD)" << " SIGNAL:" << dwSignal << std::endl;
    
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
