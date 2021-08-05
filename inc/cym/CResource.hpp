#ifndef __cym_cresource_hpp__
#define __cym_cresource_hpp__

#include "sys/CException.hpp"
#include "sys/CStream.hpp"
#include "cym/cym.hpp"
#include "cym/TManager.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>
#include <functional>
#include <any>

namespace cym {
  class CResource;
  class CResourceManager;
  class CResourceLoader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceManager;
      friend class CResourceLoader;
      enum EState { EMPTY = 0, LOADED = 1, READY = 2, };
    protected:
      EState    mState    {EState::EMPTY};
      cym::name mName;
      bool      mInstance {false};
    public:
      CResource(const cym::name& tName = "") : mName{tName} { };
      CResource(CResource&&) = delete;
      CResource(const CResource& that) {  
        mInstance = true;
        mState = that.mState;
        mName = that.mName;
      }
      virtual ~CResource() { };
    public:
      CResource& operator =(const CResource&) = delete;
      CResource& operator =(CResource&&) = delete;
    public:
      inline void             setName(const cym::name& tName) { mName = tName; }
      inline const cym::name& getName()                       { return mName; }
      inline bool             isInstance() const              { return mInstance; }
  };
  
  class CResourceLoader  {
      friend class CResource;
      friend class CResourceManager;
    protected:
      sys::string mName;
    public:
      CResourceLoader() { };
      CResourceLoader(const sys::string& tName) : mName{tName} { };
      virtual ~CResourceLoader() = default;
    public:
      virtual void load(sys::spo<CResourceLoader>) { throw sys::exception("CResourceLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      sys::string& getName() { return mName; }
  };
  
  class CResourceManager  {
      friend class CResource;
      friend class CResourceLoader;
    public:
      CResourceManager() { };
      virtual ~CResourceManager() { };
  };
  
  template<typename T> class TResourceManager : public CResourceManager {
    public:
      typedef T resource_type;
  };
}

#endif //__cym_cresource_hpp__
