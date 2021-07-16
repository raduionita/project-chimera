#ifndef __cym_cproperty_hpp__
#define __cym_cproperty_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "glm/glm.hpp"
#include "glm/CVector.hpp"

namespace cym {
  enum class EProperty : uint { LEVEL = 1, COLOR = 2, TEXTURE = 4 };
  
  class CProperty {
    public:
      using EType = EProperty;
    public:
      CProperty() = default;
      virtual ~CProperty() = default;
    public:
      inline virtual EType getType() const { throw sys::exception("CProperty::getType() NOT overriden!",__FILE__,__LINE__); }; 
  };
  
  template<EProperty E> class TProperty : public CProperty { };
  
  template<> class TProperty<EProperty::LEVEL> : public CProperty {
    protected:
      glm::real mValue;
    public:
      TProperty(const decltype(mValue)& tValue) : mValue{tValue} { }
    public:
      inline virtual EType getType() const { return EProperty::LEVEL; };  
      inline auto getValue() -> decltype(mValue)& { return mValue; }
  }; 
  
  template<> class TProperty<EProperty::COLOR> : public CProperty {
    protected:
      cym::rgba mValue;
    public:
      TProperty(const decltype(mValue)& tValue) : mValue{tValue} { }
    public:
      inline virtual EType getType() const { return EProperty::COLOR; };
      inline auto getValue() -> decltype(mValue)& { return mValue; }
  };
  
  template<> class TProperty<EProperty::TEXTURE> : public CProperty {
    protected:
      sys::sptr<CTexture> mValue;
    public:
      TProperty(const decltype(mValue)& tValue) : mValue{tValue} { }
    public:
      inline virtual EType getType() const { return EProperty::TEXTURE; };
      inline auto getValue() -> decltype(mValue)& { return mValue; }
  }; 
  
  class CGroup {
    protected:
      std::map<cym::name, sys::sptr<CProperty>> mProperties;
    public:
      sys::sptr<CProperty>& getProperty(const cym::name& tName) { return sys::find_or_throw(tName, mProperties, sys::exception("Property"+ tName +" NOT found!",__FILE__,__LINE__)); }
      template<EProperty E> void setProperty(const cym::name& tName, const sys::sptr<TProperty<E>>& pProperty) { mProperties.insert(std::pair(tName, pProperty)); }
      
  };
  
}

#endif //__cym_cproperty_hpp__
