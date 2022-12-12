#ifndef __sys_CApplication_hpp__
#define __sys_CApplication_hpp__

#include "sys/sys.hpp"
#include "sys/CException.hpp"

namespace sys {
  class CApplication {
    public:
      CApplication() { }
      virtual ~CApplication() { }
    public:
      virtual int exec(int argc, char** argv) = 0;
  };
} // namespace sys

#define DECLARE_APPLICATION(CLS)                                                                                       \
int main(int argc, char** argv) {                                                                                      \
  try {                                                                                                                \
    CLS app;                                                                                                           \
    int rez = app.exec(argc, argv);                                                                                    \
    return rez;                                                                                                        \
  } catch (sys::CException& ex) {                                                                                      \
    return -1;                                                                                                         \
  }                                                                                                                    \
}

#endif //__sys_CApplication_hpp__