#ifndef __cym_capplication_hpp__
#define __cym_capplication_hpp__

namespace cym {
  class CApplication {
    public:
    CApplication();
    virtual ~CApplication();
  
    public:
    virtual bool init();
    virtual bool free();
  };
}

#endif //__cym_capplication_hpp__
