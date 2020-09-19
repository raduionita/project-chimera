#ifndef __cym_hpp__
#define __cym_hpp__

#include "sys/sys.hpp"
#include "sys/CPointer.hpp"
#include "sys/CLogger.hpp"
#include "ogl/ogl.hpp"
#include "glm/glm.hpp"

#undef FAR
#undef NEAR

namespace cym {
  class CCore;
  class CSystem;
    class CConsole;    // a system that outputs all posted messages, also sends messages (like commands)
    // cinematics      // a system that sends messages like rotate(object)+move(camera)
    // replay/recorder // a system that records messages to be played back
  class CMessage;
  class CMessenger;    // threading: should decide on which thread a CSystem should process a message
  class CRenderer;
  class CCamera;
  class CLight;
  class CColor;
  class CMesh;
  class CResource;
    class CModel; // a group of CMesh
    class CTexture;
    class CChannel;
    class CMaterial;
    class CAnimation;
    class CShader;
  class CData;
    class CResourceInfo;
      class CTextureData;
      class CModelData;
  class CResourceLoader;
    template<typename T> class CTextureLoader;
      class CFileTextureLoader;
      class CNoiseTextureLoader;
    template<typename T> class TModelLoader;
      class CFileModelLoader;
  class CResourceInfo;
    class CTextureData;
      class CModelData;
  class CResourceManager;
    class CTextureManager;
    class CModelManager;
    class CShaderManager;
  class CObject;
    class CTexture;
    class CBuffer;
      class CDataBuffer;
        class CVertexBuffer;
        class CIndexBuffer;
    class CLayout;
      class CVertexLayout;
    class CVertexArray;
  class CUniform;
  class CVertex; // @todo: this should be a template that describes components
  class CVertexLayout;
  class CFile;
  class CCodec;
    class CDDSCodec;
    class CTGACodec;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  typedef sys::TPointer<CResource> PResource;
  typedef sys::TPointer<CTexture>  PTexture; 
  typedef sys::TPointer<CChannel>  PChannel;
  typedef sys::TPointer<CMaterial> PMaterial;
  typedef sys::TPointer<CShader>   PShader;  
  typedef sys::TPointer<CModel>    PModel;
  typedef sys::TPointer<CMesh>     PMesh;
  
  typedef sys::TPointer<CTextureManager> PTextureManager;
  typedef sys::TPointer<CModelManager>   PModelManager;
  typedef sys::TPointer<CShaderManager>  PShaderManager;
  
  typedef sys::TPointer<CCodec> PCodec;   
  
  typedef sys::TPointer<CVertexArray>  PVertexArray;
  typedef sys::TPointer<CDataBuffer>   PDataBuffer;
  typedef sys::TPointer<CVertexBuffer> PVertexBuffer;
  typedef sys::TPointer<CIndexBuffer>  PIndexBuffer;
  
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

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  
}

#endif //__cym_hpp__
