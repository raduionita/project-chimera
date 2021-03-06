#ifndef __cym_hpp__
#define __cym_hpp__

#include "sys/sys.hpp"
#include "sys/CPointer.hpp"
#include "sys/CLogger.hpp"
#include "sys/CTimer.hpp"
#include "ogl/ogl.hpp"
#include "glm/glm.hpp"

#undef FAR
#undef NEAR

// @todo: ogl vs d3d vs vlk
#if defined(USE_DIRECTX_DRIVER) 
  #define DTEXTURE d3d::CTexture
#elif defined(USE_VULKAN_DRIVER)
  #define DTEXTURE vlk::CTexture
#else // USE_OPENGL_DRIVER
  #define DTEXTURE ogl::CTexture
#endif // ifdef

namespace cym {
  class CCore;
  class CSystem;
    class CConsole;    // a system that outputs all posted messages, also sends messages (like commands)
    // cinematics      // a system that sends messages like rotate(object)+move(camera)
    // replay/recorder // a system that records messages to be played back
  class CScene;
  class CMessage;
  class CMessenger;    // threading: should decide on which thread a CSystem should process a message
  class CRenderer;
  class CCamera;
  class CLight;
  class CColor;
  class CGeometry;
  class CGeometryInput;
  class CMesh;
  class CParticle;
  class CCluster; // a group of CModel, CParticle...
  class CInstance;
  class CResource;
    class CModel; // a group of CMesh
    class CTexture;
    class CChannel;
    class CMaterial;
    class CAnimation;
    class CShader;
    class CSkeleton; //-on
  class CResourceLoader;
    class CModelLoader;
    class CMeshLoader;
    class CMaterialLoader;
    class CTextureLoader;
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
  class CVertexArray;
  class CLayout;
    class CVertexLayout;
  class CUniform;
  class CFile;
  class CCodecManager;
  class CCodec;
    class CTextureCodec;
      class CDDSCodec;
      class CTGACodec;
      class CPNGCodec;
      class CJPGCodec;
      class CKTXCodec;
    class CModelCodec;
      class CDAECodec;
      class COBJCodec;
      class CMD5Codec;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  using PShaderManager = cym::CShaderManager;
  
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
  
  using rgb   = glm::vec3;
  using rgba  = glm::vec4;
  using name  = std::string;
  using color = glm::vec4;
  
  union pixel { union rgb { sys::uint rgba; struct { sys::ubyte r, g, b, a; }; }; union bgr { sys::uint bgra; struct { sys::ubyte b, g, r, a; }; }; };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  enum class EPolymode { POINTS = 0b001, WIREFRAME = 0b010, SOLID = 0b100, };
  
  enum class ECulling { NONE, CLOCKWISE, CW = CLOCKWISE, COUNTERCLOCKWISE, CCW = COUNTERCLOCKWISE, };
  
  enum class EAnimation { LINEAR = 0, EASE_IN, EASE_OUT, EASE_IN_OUT, BOUNCE, ELASTIC };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  inline void fps(uint& nFPS) { 
    static auto tTimer {sys::CTimer::start()};
    const  auto tElapsed {tTimer.elapsed()};
    tTimer.reset();
    nFPS = 1000 / (tElapsed > 0 ? tElapsed : 1);
  }
}

#endif //__cym_hpp__
