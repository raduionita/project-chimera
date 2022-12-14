#ifndef __sys_clogger_hpp__
#define __sys_clogger_hpp__

#include "sys/sys.hpp"
#include "sys/TSingleton.hpp"

namespace sys {
    class CLogger : public TSingleton<CLogger> {
        
    };
} // namespace sys

// LOGDBG // #define LOGDBG(msg) CLogger::getInstance() << ELogLevel::DEBUG << msg << ELogManipulator::NL;
// LOGNFO
// LOGWRN
// LOGERR

#endif //__sys_clogger_hpp__