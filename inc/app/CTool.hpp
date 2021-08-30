#ifndef __app_ctool_hpp__
#define __app_ctool_hpp__

#include "cym/cym.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CShader.hpp"
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
  
// @TODO like health bards and name boxes in the game, above items/ppl
  class NWidget : public cym::TNode<cym::ENode::DRAWABLE> {
      
  };
  
  class NGrid : public cym::TNode<cym::ENode::DRAWABLE> {
    public:
      enum EGrid : int { O = 0b000, XY=0b110, XZ=0b101, YZ=0b011, XYZ=0b111 };
    protected:
      EGrid          mAxies   {EGrid::XZ};
      glm::real      mUnit    {1.f};
      sys::uint      mLength  {10u};
      cym::PGeometry mGeometry;
    public:
      using TNode<cym::ENode::DRAWABLE>::TNode;
      NGrid() : TNode<cym::ENode::DRAWABLE>("grid") { init(); }
      NGrid(const EGrid tAxies, const glm::real tUnit=1.f, const cym::uint tLength=10u) : TNode<cym::ENode::DRAWABLE>("grid"), mAxies{tAxies}, mUnit{tUnit}, mLength{tLength} { init(); }
    protected:
      void init();
    public:
      inline void             setAxies(EGrid a) { mAxies  = a; }
      inline void             addAxies(EGrid a) { mAxies  = (EGrid)(mAxies | a); }
      inline const EGrid&     getAxies()  const { return mAxies; }
      inline const glm::real& getUnit()   const { return mUnit; }
      inline const glm::uint& getLength() const { return mLength; }
      inline void setGridColor(const cym::rgb& col);
      inline void setAxiesColors(const cym::rgb& xc, const cym::rgb& yc, const cym::rgb& zc);
    public:
      virtual void draw() override;
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
      virtual void load(cym::PGeometry) override;
    public:
      inline app::NGrid& getGrid() { return mGrid; }
  };
  
  template<typename T> class TShaderLoader : public cym::TShaderLoader<T> { };
  
  template<> class TShaderLoader<app::NGrid> : public cym::CShaderLoader {
      
  };
}

#endif //__app_ctool_hpp__
