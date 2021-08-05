#ifndef __cym_clight_hpp__
#define __cym_clight_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/TInstance.hpp"

// @todo: move this as a part of CScene -> TNode<ENode::LIGHT>

// @todo: sun baked light map/shadow map transition 
  // use 2 shadow maps, fade from one to another to try to get smooth transition, when transition is complete, create the next shadow map, and start another smooth transition

namespace cym {
  class CLight; class ILight; 
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CLight {
    public:
      enum class EType : uint { DIRECT, POINT, OMNI = POINT, SPOT, AREA, };
    public:
      ~CLight() { }
    public:
      virtual inline EType getType() const { throw sys::exception("CLight::getType() NOT overridden!",__FILE__,__LINE__); }  
  };
  
  template<CLight::EType T> class TLight : public CLight { };
  
  template<> class TLight<CLight::EType::DIRECT> : public CLight { 
    public:
      virtual inline EType getType() const override { return CLight::EType::DIRECT; }
  };
  
  template<> class TLight<CLight::EType::POINT> : public CLight { 
    public:
      virtual inline EType getType() const override { return CLight::EType::POINT; }
  };
  
  template<> class TLight<CLight::EType::SPOT> : public CLight { 
    public:
      virtual inline EType getType() const override { return CLight::EType::SPOT; }
  };
  
  template<> class TLight<CLight::EType::AREA> : public CLight { 
    public:
      virtual inline EType getType() const override { return CLight::EType::AREA; }
  };
  
  // instances ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class ILight : public cym::TInstance<CLight> {
      friend class CLight;
    public:
      using cym::TInstance<CLight>::TInstance;
    public:
      inline const CLight& getLight() const { return mInstance.raw(); }
  };
}

#endif //__cym_clight_hpp__
