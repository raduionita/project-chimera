#ifndef __capplication_hpp__
#define __capplication_hpp__

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

#endif //__capplication_hpp__
