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
  class CResource;        typedef sys::ptr<CResource>       PResource;
  class CResourceManager;
  class CResourceLoader;  typedef sys::ptr<CResourceLoader> PResourceLoader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceManager;
      friend class CResourceLoader;
    public:
      enum EState { EMPTY = 0, LOADED = 1, PARTIAL = 2, READY = 3, };
    private:
      bool        mInstance{false}; // true = a copy of the original inside it's manager
    protected:
      EState      mState{EState::EMPTY};
      sys::string mName;
    public:
      CResource(const sys::string& tName = "") : mName{tName} { };
      CResource(CResource&&) = delete;
      CResource(const CResource& that) {  
        mInstance = true;
        mState = that.mState;
        mName  = that.mName;
      }
      virtual ~CResource() { };
    public:
      CResource& operator =(const CResource&) = delete;
      CResource& operator =(CResource&&) = delete;
    public:
      inline void               setName(const sys::string& tName) { mName = tName; }
      inline const sys::string& getName()                         { return mName; }
      inline bool               isInstance() const                { return mInstance; }
      inline EState             getState() const                  { return mState; }
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
      virtual void load(sys::ptr<CResourceLoader>) { throw sys::exception("CResourceLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      sys::string& getName() { return mName; }
  };
  
  class CResourceManager : public CManager {
      friend class CResource;
      friend class CResourceLoader;
    public:
      CResourceManager() = default;
      virtual ~CResourceManager() = default;
  };
  
  template<typename T> class TResourceManager : public CResourceManager {
    public:
      typedef T resource_type;
  };
}

#endif //__cym_cresource_hpp__
