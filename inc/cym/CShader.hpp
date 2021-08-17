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
      void  uniform(const CString& name, const sys::spo<CTexture>&);
      void  uniform(const CString& name, const glm::mat4& m);
      void  sampler(const CString& name, GLuint);
      void  sampler(const CString& name, const sys::spo<CTexture>&);
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CShaderLoader : public CResourceLoader {
    public:
      virtual void load(sys::spo<CResourceLoader>) override { throw sys::exception("CShaderLoader::load() NOT overriden!",__FILE__,__LINE__);  };
  };
  
  template<typename T> class TShaderLoader : public CShaderLoader { };
  
  template<> class TShaderLoader<sys::file> : public CShaderLoader {
    protected:
      std::vector<sys::file> mFile;
    public:
      virtual void load(sys::spo<CResourceLoader>) override;
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
      
  class CShaderManager : public cym::TResourceManager<CShader>, public sys::TSingleton<CShaderManager> {
    public:
      inline CShaderManager()  { SYS_LOG_NFO("cym::CShaderManager::CShaderManager()::" << this); }
      inline ~CShaderManager() { SYS_LOG_NFO("cym::CShaderManager::~CShaderManager()::" << this); }
    public:
      template<typename T> static sys::spo<CShader> load(const std::string& tName, const T& tSource) {
        
        return nullptr;
      }
  };  
}

#endif //__cym_cshader_hpp__


// 
