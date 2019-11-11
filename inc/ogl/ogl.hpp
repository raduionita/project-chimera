#ifndef __ogl_hpp__
#define __ogl_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"
#include "glc/glc.hpp"
#include "glm/glm.hpp"

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
    class CResourceData;
    class CModel; // a group of CMesh
    class CTexture;
      class CTextureData;
    class CMaterial;
    class CAnimation;
    class CShader;
  class CResourceLoader;
    class CTextureLoader;
      class CDDSTextureLoader;
      class CTGATextureLoader;
  class CResourceManager;
    class CTextureManager;
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
    class CShader;
  class CUniform;
  class CVertex; // @todo: this should be a template that describes components
  class CVertexLayout;
  class CFile;
  class CCodec;
    class CDDSCodec;
    class CTGACodec;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  typedef sys::CPointer<CResource> PResource;
  typedef sys::CPointer<CResourceData> PResourceData;
  typedef sys::CPointer<CTexture>  PTexture; 
  typedef sys::CPointer<CTextureData>  PTextureData;
  typedef sys::CPointer<CMaterial> PMaterial;
  typedef sys::CPointer<CShader>   PShader;  
  typedef sys::CPointer<CModel>    PModel;   
  
  typedef sys::CPointer<CTextureManager> PTextureManager;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  using log = sys::log;
  
  using byte   = sys::byte;
  using ubyte  = sys::ubyte;
  using tiny   = sys::tiny;
  using utiny  = sys::utiny;
  using ushort = sys::ushort;
  using uint   = sys::uint;
  using ulong  = sys::ulong;
  
  using CString                  = sys::CString;
  template<typename V> using CSet                 = sys::CSet<V>;
  template<typename K, typename V> using CMap               = sys::CMap<K,V>;
  template<typename V> using CVector              = sys::CVector<V>;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  enum class EPolymode {
    POINTS    = 0b001,
    WIREFRAME = 0b010,
    SOLID     = 0b100,
  };
  
  enum class ECulling {
    NONE,
    CLOCKWISE, CW = CLOCKWISE,
    COUNTERCLOCKWISE, CCW = COUNTERCLOCKWISE,
  };
}

#endif //__ogl_hpp__
