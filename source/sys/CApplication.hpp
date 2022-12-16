#ifndef __sys_capplication_hpp__
#define __sys_capplication_hpp__

#include "sys/sys.hpp"
#include "sys/CException.hpp"
#include "sys/CLogger.hpp"
#include "sys/CBenchmark.hpp"

namespace sys {
  class CApplication {
    public:
      CApplication() { }
      virtual ~CApplication() { }
    public:
      virtual int exec(int argc, char** argv) = 0;
  };
} // namespace sys

#undef DECLARE_APPLICATION
#define DECLARE_APPLICATION(CLS)                                                                                       \
int main(int argc, char** argv) {                                                                                      \
  LOGTAG("   ::main(int,char**)");                                                                                     \
  LOGDBG(".");                                                                                                         \
  try {                                                                                                                \
    CLS app;                                                                                                           \
    int rez = app.exec(argc, argv);                                                                                    \
    LOGNFO("::" << rez);                                                                                               \
    return rez;                                                                                                        \
  } catch (sys::CException& ex) {                                                                                      \
    LOGERR("::ERROR:" << ex);                                                                                          \
    return -1;                                                                                                         \
  }                                                                                                                    \
}

#endif //__sys_capplication_hpp__