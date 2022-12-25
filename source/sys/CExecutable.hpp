#ifndef __sys_cexecutable_hpp__
#define __sys_cexecutable_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"
#include "sys/CBenchmark.hpp"
#include "sys/CException.hpp"

namespace sys {
  class CExecutable {
    public:
      CExecutable() = default;
      virtual ~CExecutable() = default;
    public:
      virtual int exec();
      void setArguments(int argc, char* argv[]);
  };
} // namespace sys

#undef DECLARE_APPLICATION
#define DECLARE_APPLICATION(CLS)                                                                                       \
int main(int argc, char** argv) {                                                                                      \
  LOGTAG("   ::main(int,char**)");                                                                                     \
  LOGDBG(".");                                                                                                         \
  try {                                                                                                                \
    CLS exe;                                                                                                           \
    exe.setArguments(argc, argv);                                                                                      \
    int rez = exe.exec();                                                                                              \
    LOGNFO("::" << rez);                                                                                               \
    return rez;                                                                                                        \
  } catch (sys::CException& ex) {                                                                                      \
    LOGERR("::ERROR:" << ex);                                                                                          \
    return -1;                                                                                                         \
  }                                                                                                                    \
}

#endif //__sys_cexecutable_hpp__