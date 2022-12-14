#ifndef __sys_clogger_hpp__
#define __sys_clogger_hpp__

#include "sys/sys.hpp"
#include "sys/TSingleton.hpp"

#include <iostream>

namespace sys {
  class CLogger : public TSingleton<CLogger> {
    public:
      CLogger();
  };
} // namespace sys

#define LOGDBG(msg) std::cout << msg << "\n";
#define LOGNFO(msg) std::cout << msg << "\n";
#define LOGWRN(msg) std::cout << msg << "\n";
#define LOGERR(msg) std::cout << msg << "\n";
// #define LOGDBG(msg) CLogger::getInstance() << ELogLevel::DEBUG << msg << ELogManipulator::NL;
// LOGNFO
// LOGWRN
// LOGERR

#endif //__sys_clogger_hpp__