#ifndef __cym_cresource_hpp__
#define __cym_cresource_hpp__

#include "cym/cym.hpp"
#include "sys/CException.hpp"
#include "sys/CStream.hpp"

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
      enum EState { EMPTY =  0, LOADED = 1, READY  = 2, };
    protected:
      EState    mState {EState::EMPTY};
      cym::name mName;
    public:
      inline CResource(const cym::name& tName = "") : mName{tName} { };
      inline virtual ~CResource() { };
    public:
      inline void       setName(const cym::name& tName) { mName = tName; }
      inline cym::name& getName()                       { return mName; }
  };
  
  class CLoader { };
  
  class CResourceLoader : public CLoader {
      friend class CResource;
      friend class CResourceManager;
    protected:
      sys::string mName;
    public:
      CResourceLoader() { };
      CResourceLoader(const sys::string& tName) : mName{tName} { };
      virtual ~CResourceLoader() = default;
    public:
      virtual void load(sys::sptr<CResourceLoader>) { throw sys::exception("CResourceLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      sys::string& getName() { return mName; }
  };
  
  class CManager { };
  
  class CResourceManager : public CManager {
      friend class CResource;
      friend class CResourceLoader;
    public:
      CResourceManager() { };
      virtual ~CResourceManager() { };
  };
  
  template<typename T> class TManager : public CResourceManager {
    public:
      typedef T resource_type;
  };
}

#endif //__cym_cresource_hpp__
