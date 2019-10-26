#ifndef __cym_cengine_hpp__
#define __cym_cengine_hpp__

#include "cym/cym.hpp"

#include "sys/CSingleton.hpp"

namespace cym {
  class CEngine : public sys::CSingleton<CEngine> {
    protected:
      // CRenderSystem*
      // CAudioSystem*
      // CInputSystem*
      
      
      
    public:
      CEngine();
      ~CEngine();
    public:
      virtual void init();
      virtual void free();
      
      // @todo: connects(and befriends) all *System(s)
  };
}

#endif //__cym_cengine_hpp__
