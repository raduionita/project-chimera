#ifndef __sys_clogger_hpp__
#define __sys_clogger_hpp__

#ifndef LOGGER // -logger
#define LOGTAG(tag)
#define LOGDBG(msg)
#define LOGNFO(msg)
#define LOGWRN(msg)
#define LOGERR(msg)
#else // +logger

#include "sys/sys.hpp"
// #include "sys/TSingleton.hpp"

#include <iostream>

// #undef ERROR

// namespace sys {
//   class CLogger : public TSingleton<CLogger> {
//       enum class ELevel : int {
//         NONE  = 0,         //  0
//         ERROR = 1,         //  1
//         WARN  = 2 | ERROR, //  3 = 2 + 1
//         INFO  = 4 | WARN,  //  7 = 4 + 2 = 1
//         DEBUG = 8 | INFO,  // 15 = 8 + 4 + 2 + 1
//       };
//       enum class EManipulator : int {
//         END = 0,
//         NL  = 1,
//         TAB = 2,
//       };


//     public:
//       CLogger();
//   };
// } // namespace sys

[[maybe_unused]] constexpr const char* LOGPRE = "";

#define LOGTAG(tag) [[maybe_unused]] constexpr const char* LOGPRE = tag;
#define LOGDBG(msg) std::cout << "[DBG] " << LOGPRE << msg << "\n";
#define LOGNFO(msg) std::cout << "[NFO] " << LOGPRE << msg << "\n";
#define LOGWRN(msg) std::cout << "[WRN] " << LOGPRE << msg << "\n";
#define LOGERR(msg) std::cout << "[ERR] " << LOGPRE << msg << "\n";
// #define LOGDBG(msg) CLogger::getInstance() << ELogLevel::DEBUG << msg << ELogManipulator::NL;

#endif //LOGGER

#endif //__sys_clogger_hpp__