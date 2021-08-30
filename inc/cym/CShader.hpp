#ifndef __cym_cshader_hpp__
#define __cym_cshader_hpp__

#include "cym/cym.hpp"
#include "cym/CObject.hpp"
#include "cym/CResource.hpp"
#include "cym/TInstance.hpp"
#include "glm/glm.hpp"
#include "sys/CFile.hpp"

#include <string>
#include <unordered_map>

namespace cym {
  class CShader; typedef sys::ptr<CShader> PShader;
  
  // resources /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CShader : public CResource, public CObject {
      friend class CUniform;
    protected:
      struct SSource {
        std::string       name;
        GLenum            type;
        GLuint            shader;
        std::string       code;
      };
    public:
      enum EType {
      //NONE      = 0b0000'0000,
        VERTEX    = 0b00000010,
        GEOMETRY  = 0b00000100,
        TESSCTRL  = 0b00001000,
        TESSEVAL  = 0b00010000,
        FRAGMENT  = 0b00100000,
        COMPUTE   = 0b01000000,
      };
    protected:
      GLint                                   mType {0};
      std::string                             mFilepath;
      std::unordered_map<sys::CString, GLint> mUniforms;
      bool                                    mTessalated {false};
    public:
      CShader(const std::string&);
      ~CShader();
    public:
      inline bool isTessellated() const { return mTessalated; }
    public:
      // virtual void bind(CRenderer, CDrawable or CDrawcall);
      // bind(CLight) ?!
      
      void bind(bool state = true) const override;
      // uniforms
      GLint uniform(const CString& name);
      void  uniform(const CString& name, float x, float y, float z, float w);
      void  uniform(const CString& name, float x);
      void  uniform(const CString& name, const sys::ptr<CTexture>&);
      void  uniform(const CString& name, const glm::mat4& m);
      void  sampler(const CString& name, GLuint);
      void  sampler(const CString& name, const sys::ptr<CTexture>&);
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CShaderLoader : public CResourceLoader {
    public:
      virtual void load(sys::ptr<CResourceLoader>) override { throw sys::exception("CShaderLoader::load() NOT overriden!",__FILE__,__LINE__);  };
  };
  
  template<typename T> class TShaderLoader : public CShaderLoader { };
  
  template<> class TShaderLoader<sys::file> : public CShaderLoader {
    protected:
      std::vector<sys::file> mFile;
    public:
      virtual void load(sys::ptr<CResourceLoader>) override;
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
      
  class CShaderManager : public cym::TResourceManager<CShader>, public sys::TSingleton<CShaderManager> {
      friend class cym::CShader;
      friend class cym::CShaderLoader;
      friend class sys::TSingleton<CShaderManager>;
    protected:
      sys::table<sys::string,PShader> mShaders;
    protected:
      CShaderManager();
      ~CShaderManager();
    public:
      /* boot up shader manager */
      static void boot();
      /* find shader using hints */
      static PShader find(int iHints);
      /* load shader and remember it */
      template<typename T> static PShader load(const std::string& tName, const T& tSource) {
        
        return nullptr;
      }
  };  
}

#endif //__cym_cshader_hpp__


// 
