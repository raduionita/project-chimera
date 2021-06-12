#ifndef __sys_capplication_hpp__
#define __sys_capplication_hpp__

namespace sys {
  class CApplication {
    public:
    CApplication();
    virtual ~CApplication();
  
    public:
    virtual bool init();
    virtual bool free();
  };
}

#endif //__sys_capplication_hpp__
