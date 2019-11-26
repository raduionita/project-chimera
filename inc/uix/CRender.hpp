#ifndef __uix_crender_hpp__
#define __uix_crender_hpp__

#include "uix.hpp"
#include "CContext.hpp"
#include "CListener.hpp"

namespace uix {
  class CRender {
    protected:
      friend class CContext;
    protected:
      CContext* mContext {nullptr};
    public:
      CRender();
      virtual ~CRender();
    protected:
      bool init(CWindow*, const CContext::SConfig&);
    public:
      bool        swap()    const;
      bool        current() const;
      bool        clear(int = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT) const;
      bool        reset()   const;
      const char* version() const;
    public: // events
      void onResize(CEvent*);
  };
}

#endif //__uix_crender_hpp__
