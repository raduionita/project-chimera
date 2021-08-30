#ifndef __cym_tproperty_hpp__
#define __cym_tproperty_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "glm/glm.hpp"
#include "glm/CVector.hpp"

namespace cym {
  enum class EProperty : uint { VALUE = 1, COLOR = 2, TEXTURE = 4 };
  
  class CProperty;
  template<EProperty E> class TProperty;
  
  typedef sys::ptr<CProperty> PProperty;
  
  // properties //////////////////////////////////////////////////////////////////////////////////////////////////////
  
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
  
  template<> class TProperty<EProperty::VALUE> : public CProperty {
    protected:
      glm::real mValue;
    public:
      TProperty(const decltype(mValue)& tValue) : mValue{tValue} { }
    public:
      inline virtual EType getType() const { return EProperty::VALUE; };  
      inline auto getValue() -> decltype(mValue)& { return mValue; }
  }; 
  
  template<> class TProperty<EProperty::COLOR> : public CProperty {
    protected:
      cym::rgba mColor;
    public:
      TProperty(const decltype(mColor)& tValue) : mColor{tValue} { }
    public:
      inline virtual EType getType() const { return EProperty::COLOR; };
      inline auto getColor() -> decltype(mColor)& { return mColor; }
  };
  
  template<> class TProperty<EProperty::TEXTURE> : public CProperty {
    protected:
      sys::ptr<CTexture> mTexture;
    public:
      TProperty(const decltype(mTexture)& tTexture) : mTexture{tTexture} { }
    public:
      inline virtual EType getType() const { return EProperty::TEXTURE; };
      inline auto getTexture() -> decltype(mTexture)& { return mTexture; }
  }; 
}

#endif //__cym_tproperty_hpp__
