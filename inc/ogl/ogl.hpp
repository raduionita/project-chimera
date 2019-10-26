#ifndef __glo_hpp__
#define __glo_hpp__

#include "glc/glc.hpp"
#include "sys/sys.hpp"
#include "sys/CLogger.hpp"

#undef FAR
#undef NEAR

namespace ogl {
  class CEngine;
  class CSystem;
    class CConsole;    // a system that outputs all posted messages, also sends messages (like commands)
    // cinematics      // a system that sends messages like rotate(object)+move(camera)
    // replay/recorder // a system that records messages to be played back
  class CMessage;
  class CMessenger;    // threading: should decide on which thread a CSystem should process a message
  class CRenderer;
  class CCamera;
  class CLight;
  class CResource;
    class CModel; // a group of CMesh
    class CTexture;
    class CMaterial;
    class CAnimation;
  class CShader;
  class CObject;
    class CTexture;
    class CBuffer;
      class CDataBuffer;
        class CVertexBuffer;
        class CIndexBuffer;
    class CLayout;
      class CVertexLayout;
    class CArray;
      class CVertexArray;
    class CProgram;
    class CUniform;
  class CVertex; // @todo: this should be a template that describes components
  class CVertexLayout;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  using log = sys::log;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  enum EPolymode {
    POINTS,
    WIREFRAME,
    SOLID,
  };
  
  enum ECulling {
    NONE,
    CLOCKWISE, CW = CLOCKWISE,
    COUNTERCLOCKWISE, CCW = COUNTERCLOCKWISE,
  };
}



#endif //__glo_hpp__
