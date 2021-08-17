#include "app/CTool.hpp"

namespace app {
  void NGrid::init() {
    SYS_LOG_NFO("app::NGrid::init()");
    
    sys::spo<app::TGeometryLoader<NGrid>> pLoader {new app::TGeometryLoader<NGrid>{*this}};
    
    mGeometry = cym::CGeometryManager::load(sys::spo<cym::CGeometryLoader>{pLoader});
  }
  
  void TGeometryLoader<app::NGrid>::load(sys::spo<cym::CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TGeometryLoader<app::NGrid>::load(sys::spo<CResourceLoader>)");
    
    auto        pGeometryLoader = sys::static_pointer_cast<TGeometryLoader<app::NGrid>>(pResourceLoader);
    app::NGrid& rGrid           = pGeometryLoader->getGrid();
    auto& rGeometryBuffer       = pGeometryLoader->getGeometryBuffer();
    
    auto& rPositions = rGeometryBuffer.getStream().make("positions", new cym::CPositionInput);
    auto& rLayout    = rGeometryBuffer.getLayout();
    
    const glm::real& kUnit     {rGrid.getUnit()};   //  1.f
    const cym::uint  kNumLines {11};                // 11u(=10+1)
    const glm::real  kLength   {kNumLines * kUnit}; // 11.f
    const glm::real  kStart    {-kLength/2};        // -5.f
    const glm::real  kEnd      { kLength/2};        // +5.f
    const glm::uint  kAxies    {3};
    const cym::uint  kNumVertices {/*grid*/kAxies * 4 * kNumLines + /*axor*/ 4};   // | | | | | | | | 
    const cym::uint  kNumIndices  {/*grid*/kAxies * 4 * kNumLines + /*axor*/ 6};   // +-+-+-+-
    
    
    rPositions.grow(kNumVertices);
    rLayout.grow(kNumIndices);
    
    int ii {0}, j {0}, pi{0};
    
    // xy
    {
      auto& pXYMeshLoader = pGeometryLoader->getMeshLoader("xy");
      
      pXYMeshLoader->setRangeStart(rLayout.size());
      
      for (glm::real fi = kStart; fi < kLength; fi+=kUnit) {
        // -x ... +x
        rPositions[pi+0] = glm::vec3{fi, 0.f,0.f}; // 0,0 -> 0,10
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{fi,kEnd,0.f}; // 1,0 -> 1,10
        rLayout[ii++]    = pi+1;
        pi += 2;
        // -y ... +y
        rPositions[pi+0] = glm::vec3{ 0.f,fi,0.f}; // 0,0 -> 10,0
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{kEnd,fi,0.f}; // 0,1 -> 10,1
        rLayout[ii++]   = pi+1;
        pi += 2;
      }
      
      pXYMeshLoader->setRangeStart(rLayout.size());
            
      pXYMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pXYMeshLoader->getMaterialLoader()->getChannelLoader(cym::CChannel::DIFFUSE)->setColor(cym::rgba{1.f});
    }
    // xz
    {
      auto& pXZMeshLoader = pGeometryLoader->getMeshLoader("xz");
      
      pXZMeshLoader->setRangeStart(rLayout.size());
      
      for (glm::real fi = kStart; fi < kLength; fi+=kUnit) {
        // -x ... +x
        rPositions[pi+0] = glm::vec3{fi,0.f, 0.f}; // 0,0 -> 0,10
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{fi,0.f,kEnd}; // 1,0 -> 1,10
        rLayout[ii++]    = pi+1;
        pi += 2;
        // -z ... +z
        rPositions[pi+0] = glm::vec3{ 0.f,0.f,fi}; // 0,0 -> 10,0
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{kEnd,0.f,fi}; // 0,1 -> 10,1
        rLayout[ii++]   = pi+1;
        pi += 2;
      }
      
      pXZMeshLoader->setRangeEnd(rLayout.size());
      
      pXZMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pXZMeshLoader->getMaterialLoader()->getChannelLoader(cym::CChannel::DIFFUSE)->setColor(cym::rgba{1.f});
    }
    // yz
    {
      auto& pYZMeshLoader              = pGeometryLoader->getMeshLoader("yz");
      
      pYZMeshLoader->setRangeStart(rLayout.size());
      
      for (glm::real fi = kStart; fi < kLength; fi+=kUnit) {
        // -y ... +y
        rPositions[pi+0] = glm::vec3{0.f,fi, 0.f}; // 0,0 -> 0,10
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{0.f,fi,kEnd}; // 1,0 -> 1,10
        rLayout[ii++]    = pi+1;
        pi += 2;
        // -z ... +z
        rPositions[pi+0] = glm::vec3{0.f, 0.f,fi}; // 0,0 -> 10,0
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{0.f,kEnd,fi}; // 0,1 -> 10,1
        rLayout[ii++]   = pi+1;
        pi += 2;
      }
      
      pYZMeshLoader->setRangeStart(rLayout.size());
            
      pYZMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pYZMeshLoader->getMaterialLoader()->getChannelLoader(cym::CChannel::DIFFUSE)->setColor(cym::rgba{1.f});
    }
    // axies
    {
      auto& pAxorMeshLoader = pGeometryLoader->getMeshLoader("axor");
      
      pAxorMeshLoader->setRangeStart(rLayout.size());
      
      rPositions[pi+0] = glm::vec3{0.f};
      rPositions[pi+1] = glm::vec3{1.f, 0.f, 0.f};
      rLayout[ii++] = pi; rLayout[ii++] = pi+1;     // 0 -> x
      rPositions[pi+2] = glm::vec3{0.f, 1.f, 0.f};  
      rLayout[ii++] = pi; rLayout[ii++] = pi+2;     // 0 -> y
      rPositions[pi+3] = glm::vec3{0.f, 0.f, 1.f};
      rLayout[ii++] = pi; rLayout[ii++] = pi+3;     // 0 -> z
      pi+=4;
      
      pAxorMeshLoader->setRangeEnd(rLayout.size());
      
      pAxorMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pAxorMeshLoader->getMaterialLoader()->getChannelLoader(cym::CChannel::DIFFUSE)->setColor(cym::rgba{1.f});
    }
  }
}
