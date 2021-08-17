#ifndef __app_ctool_hpp__
#define __app_ctool_hpp__

#include "cym/cym.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CScene.hpp"
#include "glm/CVector.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CAABB.hpp"
#include "glm/CFrustum.hpp"

namespace app {
  class CTool {
    public:
      virtual ~CTool() = default;
  };
  
  class CGizmo : public CTool {
      
  };
  
  class CCage : public CTool {
      
  };
  
  class NGrid : public cym::TNode<cym::ENode::BASIC> {
    public:
      enum EGrid { XY=0b110, XZ=0b101, YZ=0b011, XYZ=0b111 };
    protected:
      EGrid                    mAxies {EGrid::XZ};
      glm::real                mUnit  {glm::ONE};
    //sys::uint                mLines {10};
      sys::spo<cym::CGeometry> mGeometry;
    public:
      using TNode<cym::ENode::BASIC>::TNode;
      NGrid() : TNode<cym::ENode::BASIC>("grid") { init(); }
      NGrid(const EGrid tAxies, const glm::real tUnit=glm::ONE/*, const sys::uint tLines=10*/) : TNode<cym::ENode::BASIC>("grid"), mAxies{tAxies}, mUnit{tUnit} { init(); }
    protected:
      void init();
    public:
      inline const glm::real& getUnit()  const { return mUnit; }
    //inline const glm::uint& getLines() const { return mLines; }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> class TGeometryLoader : public cym::TGeometryLoader<T> { };
  
  template<> class TGeometryLoader<app::NGrid> : public cym::CGeometryLoader {
    protected:
      app::NGrid& mGrid;
    public:
      inline TGeometryLoader(app::NGrid& rGrid, sys::uint eFlags = EFlag::DEFAULT) : cym::CGeometryLoader(name(rGrid), eFlags), mGrid{rGrid} { }
    public:
      inline static sys::string name(app::NGrid& g, sys::uint e=EFlag::DEFAULT) { return std::string("grid:") + '|' + sys::to_string(g.getUnit()); }
      virtual void load(sys::spo<CResourceLoader>) override;
      inline app::NGrid& getGrid() { return mGrid; }
  };
}

#endif //__app_ctool_hpp__
