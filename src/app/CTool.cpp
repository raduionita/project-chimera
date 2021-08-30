#include "app/CTool.hpp"

namespace app {
  void NGrid::init() {
    SYS_LOG_NFO("app::NGrid::init()");
    
    sys::ptr<app::TGeometryLoader<NGrid>> pLoader {new app::TGeometryLoader<NGrid>{*this}};
    
    mGeometry = cym::CGeometryManager::load(cym::PGeometryLoader{pLoader});
  }
  
  void NGrid::draw() {
    if (mGeometry->getState() == cym::CResource::EState::READY) {
      for (const auto& [tName,pMesh] : mGeometry->getMeshes()) {
        if (!pMesh->isHidden()) {
          GLCALL(::glDrawElementsInstanced((GLenum)(pMesh->getPrimitive()), pMesh->getRange().getCount(), pMesh->getRange().getType(), (void*)(pMesh->getRange().getStart() * cym::sizeOf(pMesh->getRange().getType())), 3));
        }
      }
    }
    // mGeometry->draw();
  }
  
  void TGeometryLoader<app::NGrid>::load(cym::PGeometry pGeometry) {
    SYS_LOG_NFO("cym::TGeometryLoader<app::NGrid>::load(cym::PGeometry)");
    
    auto        pGeometryLoader = this; // sys::static_pointer_cast<TGeometryLoader<app::NGrid>>(pResourceLoader);
    app::NGrid& rGrid           = pGeometryLoader->getGrid();
    auto& rGeometryBuffer       = pGeometryLoader->getGeometryBuffer();
    
    auto& rPositions = rGeometryBuffer.getStream().make("positions", new cym::CPositionInput);
    auto& rLayout    = rGeometryBuffer.getLayout();
    
    const NGrid::EGrid& rAxies    {rGrid.getAxies()};  // XZ
    const glm::real&    rUnit     {rGrid.getUnit()};   // 1.f
    const glm::uint&    rLength   {rGrid.getLength()};// 10
    
    const cym::uint  kNumLines {rLength + 1u}; // 11u(=10+1)
    const glm::real  kStart    {-((kNumLines-1u)*rUnit)/2.f};        // -5.f
    const glm::real  kEnd      { ((kNumLines-1u)*rUnit)/2.f};        // +5.f
    const glm::uint  kAxies    {3u};
    const cym::uint  kNumVertices {/*grid*/kAxies * 4 * kNumLines + /*axor*/ 4};   // | | | | | | | | 
    const cym::uint  kNumIndices  {/*grid*/kAxies * 4 * kNumLines + /*axor*/ 6};   // +-+-+-+-
    
    
    rPositions.grow(kNumVertices);
    rLayout.grow(kNumIndices);
    
    cym::uint ii {0}, pi{0}; 
    glm::real fi;
    
// @TODO: geometry/mesh variables 
    
    // xy
    {
      auto& pXYMeshLoader = pGeometryLoader->getMeshLoader("xy");
      
      pXYMeshLoader->setRangeStart(ii);
      
      for (fi = kStart; fi <= kEnd; fi+=rUnit) {
        // -x ... +x
        rPositions[pi+0] = glm::vec3{fi,kStart,0.f}; // 0,0 -> 0,10
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{fi,  kEnd,0.f}; // 1,0 -> 1,10
        rLayout[ii++]    = pi+1;
        pi += 2;
        // -y ... +y
        rPositions[pi+0] = glm::vec3{kStart,fi,0.f}; // 0,0 -> 10,0
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{  kEnd,fi,0.f}; // 0,1 -> 10,1
        rLayout[ii++]    = pi+1;
        pi += 2;
      }
      
      pXYMeshLoader->setRangeEnd(ii);
            
      pXYMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pXYMeshLoader->getMaterialLoader()->getChannelLoader(cym::EChannel::DIFFUSE)->setColor(cym::rgba{1.f});
      
      pXYMeshLoader->setHidden((rAxies & NGrid::EGrid::XY) != NGrid::EGrid::XY);
    }
    // xz
    {
      auto& pXZMeshLoader = pGeometryLoader->getMeshLoader("xz");
      
      pXZMeshLoader->setRangeStart(ii);
      
      for (fi = kStart; fi <= kEnd; fi+=rUnit) {
        // -x ... +x
        rPositions[pi+0] = glm::vec3{fi,0.f,kStart}; // 0,0 -> 0,10
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{fi,0.f,  kEnd}; // 1,0 -> 1,10
        rLayout[ii++]    = pi+1;
        pi += 2;
        // -z ... +z
        rPositions[pi+0] = glm::vec3{kStart,0.f,fi}; // 0,0 -> 10,0
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{  kEnd,0.f,fi}; // 0,1 -> 10,1
        rLayout[ii++]    = pi+1;
        pi += 2;
      }
      
      pXZMeshLoader->setRangeEnd(ii);
      
      pXZMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pXZMeshLoader->getMaterialLoader()->getChannelLoader(cym::EChannel::DIFFUSE)->setColor(cym::rgba{1.f});
      
      pXZMeshLoader->setHidden((rAxies & NGrid::EGrid::XZ) != NGrid::EGrid::XZ);
    } 
    // yz
    {
      auto& pYZMeshLoader              = pGeometryLoader->getMeshLoader("yz");
      
      pYZMeshLoader->setRangeStart(ii);
      
      for (fi = kStart; fi <= kEnd; fi+=rUnit) {
        // -y ... +y
        rPositions[pi+0] = glm::vec3{0.f,fi,kStart}; // 0,0 -> 0,10
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{0.f,fi,  kEnd}; // 1,0 -> 1,10
        rLayout[ii++]    = pi+1;
        pi += 2;
        // -z ... +z
        rPositions[pi+0] = glm::vec3{0.f,kStart,fi}; // 0,0 -> 10,0
        rLayout[ii++]    = pi+0;
        rPositions[pi+1] = glm::vec3{0.f,  kEnd,fi}; // 0,1 -> 10,1
        rLayout[ii++]    = pi+1;
        pi += 2;
      }
      
      pYZMeshLoader->setRangeEnd(ii);
            
      pYZMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pYZMeshLoader->getMaterialLoader()->getChannelLoader(cym::EChannel::DIFFUSE)->setColor(cym::rgba{1.f});
      
      pYZMeshLoader->setHidden((rAxies & NGrid::EGrid::YZ) != NGrid::EGrid::YZ);
    }
    // axies
    {
      auto& pAxorMeshLoader = pGeometryLoader->getMeshLoader("axor");
      
      pAxorMeshLoader->setRangeStart(ii);
      
      rPositions[pi+0] = glm::vec3{0.f};
      rPositions[pi+1] = glm::vec3{rUnit * rLength, 0.f, 0.f};
      rLayout[ii++] = pi; rLayout[ii++] = pi+1;     // 0 -> x
      rPositions[pi+2] = glm::vec3{0.f, rUnit * rLength, 0.f};  
      rLayout[ii++] = pi; rLayout[ii++] = pi+2;     // 0 -> y
      rPositions[pi+3] = glm::vec3{0.f, 0.f, rUnit * rLength};
      rLayout[ii++] = pi; rLayout[ii++] = pi+3;     // 0 -> z
      // pi+=4;
      
      pAxorMeshLoader->setRangeEnd(ii);
      
      pAxorMeshLoader->setPrimitive(cym::EPrimitive::LINES);
      
      pAxorMeshLoader->getMaterialLoader()->getChannelLoader(cym::EChannel::DIFFUSE)->setColor(cym::rgba{1.f});
    }
  }
}


// @TODO node:entity grid
       //   node:model = grid
       //     geometry = grid
       //       mesh = xy
       //       mesh = xz
       //       mesh = yz
       //   node:model = axor
       //     geometry = axor
       
// @TODO node:entity gizmo
      //   node:model
      //     geometry = spin
      //     geometry = move
      //     geometry = grow
