#ifndef __cym_cinstance_hpp__
#define __cym_cinstance_hpp__

#include "cym/cym.hpp"
#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"

namespace cym {
  class CInstance;
  template<typename T> class TInstance;
  class CInstanceRegistry;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  class CInstanceRegistry : public sys::TSingleton<CInstanceRegistry> {
      friend class CInstance;
    protected:
      sys::map<CInstance*,bool&> mInstances;
    public:
      ~CInstanceRegistry();
  };
  
  class CInstance {
      friend class CInstanceRegistry;
    protected:
      bool mLoaded {false};
    public:
      CInstance();
      virtual ~CInstance();
    public:
      inline bool isLoaded() const { return mLoaded; }
  };
  
  template<typename T> class TInstance : public CInstance {
      friend class CInstance;
      friend class CInstanceRegistry;
    public:
      typedef           T resource_type;
      typedef           T* pointer_type;
      typedef sys::sptr<T> instance_type;
    protected:
      sys::sptr<T> mInstance {nullptr};
    public:
      using CInstance::CInstance;
    public:
      TInstance(sys::sptr<T> pInstance) : mInstance{pInstance} { mLoaded = (mInstance == true); }
      TInstance(const TInstance& that) : mInstance{that.mInstance} { mLoaded = (mInstance == true); }
      inline ~TInstance() { CYM_LOG_NFO("cym::TInstance<"<< typeid(T).name() <<">::~TInstance()::" << this); }
    public:
      // access operators
      T& operator  *() const noexcept { return mInstance.raw(); }
      T* operator ->() const noexcept { return mInstance.ptr(); }
      // assignment operators
      TInstance& operator  =(const TInstance& that) { if (this != &that) { mInstance = that.mInstance; mLoaded = (mInstance == true); } return *this; }
      TInstance& operator  =(sys::sptr<T> pInstance) { mInstance = pInstance; mLoaded = (mInstance == true); }
      // bool operators
      bool       operator ==(std::nullptr_t) { return mInstance == nullptr; }
      bool       operator ==(bool state)     { return state ? mInstance != nullptr : mInstance == nullptr; }
      bool       operator  !()               { return mInstance == nullptr; }
      // cast operators
      operator            bool() const { return mInstance != nullptr; }
      inline operator       T*() const { return mInstance.ptr(); }
      inline operator const T*() const { return mInstance.ptr(); }
      inline operator        T() const { return mInstance.raw(); }
      inline operator const  T() const { return mInstance.raw(); }
    protected:
      virtual void             init() { }
    public:
      static inline TInstance* from(sys::sptr<T> tSource) { auto pInstance {new TInstance<T>(tSource)}; return pInstance; }
      inline virtual void      load(sys::sptr<T> pInstance) final { mInstance = pInstance; mLoaded = (mInstance == true); } 
    public:
      inline sys::sptr<T> getInstance() const { return mInstance; }
      inline const T*    getPointer()  const { return mInstance.ptr(); }
      inline const T&    getResource() const { return mInstance.raw(); }
  }; 
  
  // template<> class TInstance<int> : public 
}

#endif //__cym_cinstance_hpp__
