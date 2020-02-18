namespace app
{
  class CBeing
  
  class CMonster : CBeing
  
  class CHuman : CBeing
  
  class CAnimal : CBeing
  
  auto monster = new CMonster{};
  
  // /////////////////////////////////////
  
  
}

namespace gfx
{
  class CScene
    # mOctree : COctree
  
  class COctree
    # mRoot  : node_t<CElement>
  
  class CElement        // CNode
  
  class CQuery          // query scene using camera's fustrum
  
  
  
  class CModel
    # mPosition         // view space 
    # mMeshes : std::map<string, CMesh>

  class CMesh
    # mMaterial
  
  class CAnimation
    # mSkeleton 
    # mFrames : std::array<frame_t>
    # mDuration : int
    # mTime : int
    # mRate : int    // fps
  
  class CMaterial
    # mChannels : std::map<EType, CChannel>
    
  class CChannel
    # mColor : rgba
    # mTexture : CTexture
  
  class CTexture
  
  class CBuffer
    # mBuffer : GLuint
  
  class CProgram
  
  class CShader
  
  class CRenderer
  
  class CCamera
  
  class CLight
  
  class CShadow         // CShadowFramebuffer OR CShadowbuffer
  
  class CFramebuffer
  
  class CRenderbuffer
}

