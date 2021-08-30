#ifndef __cym_crendersystem_hpp__
#define __cym_crendersystem_hpp__

#include "cym/cym.hpp"
#include "sys/TPointer.hpp"
#include "sys/TSingleton.hpp"

namespace cym {
// @todo: there should be an extended version of this for each type of renderer OGL3 OGLES DX12 VLK
  
// @TODO init on core

  class CRenderSystem : public sys::TSingleton<CRenderSystem> {
      enum EEnable : sys::bitfield /*=uint*/ {
        ENABLE              = 0,
        BLEND               = 1 << 1,
        CULL_FACE           = 1 << 2,
        DEPTH_TEST          = 1 << 3,
        POLYGON_OFFSET_LINE = 1 << 4,
      };
    private:
      bool                     mInited {false};
    protected:
      sys::bitfield            mEnabled;
      GLenum                   mCullFace;    // GL_BACK
      GLenum                   mFrontFace;   // GL_CCW
      GLenum                   mDepthFunc;   // GL_LEQUAL
      GLenum                   mDepthMask;   // GL_TRUE
      std::pair<GLenum,GLenum> mBlendFunc;   // GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
      std::pair<GLenum,GLenum> mPolygonMode; // GL_FRONT,GL_FILL (default) // GL_FRONT_AND_BACK,GL_LINE (wireframe)
    public:
      CRenderSystem();
      virtual ~CRenderSystem();
    protected:
      bool init();
      void free();
    public:
      inline static void boot() { CRenderSystem::getSingleton(); }
    public:
      inline void useBlend(bool b) { if /* on */ (b) { if ((mEnabled & BLEND) == 0) { GLCALL(::glEnable(GL_BLEND)); mEnabled |= BLEND; } /* do nothing if it has flag */ } else if /*off*/  ((mEnabled & BLEND)) { GLCALL(::glDisable(GL_BLEND)); mEnabled &= ~BLEND; } /* else do nothing if it doesn't have flag */ }
      inline bool setBlendFunc(GLenum s, GLenum d) { if (mBlendFunc.first != s || mBlendFunc.second != d) { useBlend(true); GLCALL(::glBlendFunc(s,d)); mBlendFunc.first = s; mBlendFunc.second = d; return true; } return false; }
      
      inline void useCullFace(bool b)   { if /* on */ (b) { if ((mEnabled & CULL_FACE) == 0) { GLCALL(::glEnable(GL_CULL_FACE)); mEnabled |= CULL_FACE; } /* do nothing if it has flag */ } else if /*off*/  ((mEnabled & CULL_FACE)) { GLCALL(::glDisable(GL_CULL_FACE)); mEnabled &= ~CULL_FACE; } /* else do nothing if it doesn't have flag */ }
      inline bool setCullFace(GLenum e) { if (mCullFace != e) { useCullFace(true); GLCALL(::glCullFace(e)); mCullFace = e; return true; } return false; }
      
      inline bool setFrontFace(GLenum e) { if (mFrontFace != e) { GLCALL(::glFrontFace(e)); mFrontFace = e; return true; } return false; }
      
      inline void useDepthTest(bool b) { if /* on */ (b) { if ((mEnabled & DEPTH_TEST) == 0) { GLCALL(::glEnable(GL_DEPTH_TEST)); mEnabled |= DEPTH_TEST; } /* do nothing if it has flag */ } else if /*off*/  ((mEnabled & DEPTH_TEST)) { GLCALL(::glDisable(GL_DEPTH_TEST)); mEnabled &= ~DEPTH_TEST; } /* else do nothing if it doesn't have flag */ }
      inline bool setDepthTest(GLenum f, GLenum m) { return setDepthFunc(f) && setDepthMask(m); }
      inline bool setDepthFunc(GLenum e) { if (mDepthFunc != e) { useDepthTest(true); GLCALL(::glDepthFunc(e)); mDepthFunc = e; return true; } return false; }
      inline bool setDepthMask(GLenum e) { if (mDepthMask != e) { useDepthTest(true); GLCALL(::glDepthMask(e)); mDepthMask = e; return true; } return false; }
  
      inline void usePolygonOffsetLine(bool b) { if /* on */ (b) { if ((mEnabled & POLYGON_OFFSET_LINE) == 0) { GLCALL(::glEnable(GL_POLYGON_OFFSET_LINE)); mEnabled |= POLYGON_OFFSET_LINE; } /* do nothing if it has flag */ } else if /*off*/  ((mEnabled & POLYGON_OFFSET_LINE)) { GLCALL(::glDisable(GL_POLYGON_OFFSET_LINE)); mEnabled &= ~POLYGON_OFFSET_LINE; } /* else do nothing if it doesn't have flag */ }
      inline bool setPolygonMode(GLenum f, GLenum m) { 
        if (mPolygonMode.first != f || mPolygonMode.second != m) {
          mPolygonMode.first  = f;
          mPolygonMode.second = m;
          if (m == GL_LINE) { 
            usePolygonOffsetLine(true); 
            GLCALL(::glPolygonOffset(-1.f,-1.f)); 
            GLCALL(::glPolygonMode(f,m)); 
            GLCALL(::glLineWidth(1.f)); 
          } else { 
            usePolygonOffsetLine(false); 
            GLCALL(::glPolygonMode(f,m)); 
            if (m == GL_POINT) { 
              // @todo: ?
            } else /* GL_FILL */ { 
              // @todo: ?
            } 
          } 
        } 
        return false; 
      }
 
      inline bool setViewport(int x, int y, int w, int h) { GLCALL(::glViewport(0,0,w,h)); return true; } 
  };
}

#endif //__cym_crendersystem_hpp__
