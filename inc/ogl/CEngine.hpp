#ifndef __ogl_cengine_hpp__
#define __ogl_cengine_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CTexture.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace ogl {
  class CEngine : public sys::CSingleton<CEngine> {
    protected:
      // CRenderSystem*
      // CAudioSystem*
      // CInputSystem*
      
      CTextureManager* mTextureManager {nullptr};
    public:
      CEngine();
      ~CEngine();
    protected:
      virtual void init();
      virtual void free();
      template <typename T> T*                  load() { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      template <> virtual ogl::CTextureManager* load<ogl::CTextureManager>();
    public:
      template <typename T> T*                  load(T*) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      template <> virtual ogl::CTextureManager* load<ogl::CTextureManager>(ogl::CTextureManager*);
      // @todo: connects(and befriends) all *System(s)
  };
}

#endif //__ogl_cengine_hpp__
