#include "cym/CGeometry.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  CMesh::~CMesh() {
    SYS_LOG_NFO("cym::CMesh::~CMesh()::" << this);
  }
  
  CGeometry::CGeometry(const sys::string& tName) : cym::CResource(tName) {
    SYS_LOG_NFO("cym::CGeometry::CGeometry(const sys::string&)::" << this);
  }
  
  CGeometry::CGeometry(sys::spo<CGeometryLoader> pLoader) {
    SYS_LOG_NFO("cym::CGeometry::CGeometry(sys::spo<CGeometryLoader>)::" << this);
    load(pLoader);
  }
  
  CGeometry::~CGeometry() {
     SYS_LOG_NFO("cym::CGeometry::~CGeometry()::" << this << " NAME:" << mName);
     //CGeometryManager::kill(this->mName);
  }
  
  void CGeometry::load(sys::spo<CGeometryLoader> pLoader) {
    SYS_LOG_NFO("cym::CGeometry::load(sys::spo<CGeometryLoader>)::" << this);
    
    cym::CGeometryBuffer& rBuffer = pLoader->mGeometryBuffer;
    
    rBuffer.pack();
    
    mVAO = new cym::CVertexArray;
    mIBO = new cym::CIndexBuffer{rBuffer.getLayout().data(), rBuffer.getLayout().size(), rBuffer.getLayout().count()};
    mVLO = new cym::CVertexLayout{cym::CVertexLayout::SEQUENTIAL};
    mVBO = new cym::CVertexBuffer{rBuffer.getStream().size(), rBuffer.getStream().count()};
  
// @todo merge geometries: CGeometryBuffer + CGeometryBuffer or rBuffer.concat(CGeometry) 

// @todo: CGeometryBuffer could/should have an array of CGeometries

    // for (auto& rBuffer : rData.geometries) 
    for (auto&& [name,in] : rBuffer.getInputs()) {
      // load vbo & layout
      mVBO->data(in);
      mVLO->read(in);
      // infer mAABB from geometry
      if (in->attribute() == EVertexAttribute::POSITION) {
        auto pi = static_cast<cym::CPositionInput*>(in);
        for (auto& tVec : pi->input()) {
          mAABB.min.x = glm::min(mAABB.min.x,tVec.x); mAABB.min.y = glm::min(mAABB.min.y,tVec.y); mAABB.min.z = glm::min(mAABB.min.z,tVec.z);
          mAABB.max.x = glm::max(mAABB.max.x,tVec.x); mAABB.max.y = glm::max(mAABB.max.y,tVec.y); mAABB.max.z = glm::max(mAABB.max.z,tVec.z);
        }
      }
    }
    
    mVAO->load(*mVBO,*mVLO);
  }
  
  void CGeometry::draw() {
    mVAO->bind(); 
    mIBO->bind(); 
    for (auto& [tName,pMesh] : mMeshes) {
      GLCALL(::glDrawElements((GLenum)(pMesh->mPrimitive), pMesh->mRange.getCount(), pMesh->mRange.getType(), (void*)(pMesh->mRange.getStart() * cym::sizeOf(pMesh->mRange.getType()))));
    }
  }
  
  void CMesh::draw() { mGeometry->mVAO->bind(); mGeometry->mIBO->bind(); GLCALL(::glDrawElements((GLenum)(mPrimitive), mRange.getCount(), mRange.getType(), (void*)(mRange.getStart() * cym::sizeOf(mRange.getType())))); }
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CGeometryManager::CGeometryManager()  { 
    SYS_LOG_NFO("cym::CGeometryManager::CGeometryManager()::" << this); 
  }
  
  CGeometryManager::~CGeometryManager() { 
    SYS_LOG_NFO("cym::CGeometryManager::~CGeometryManager()::" << this);
    //for (auto it = mGeometrys.begin(); it != mGeometrys.end(); )
      //CGeometryManager::kill(it->second);
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TGeometryLoader<sys::file>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TGeometryLoader<sys::file>::load(sys::spo<CResourceLoader>)::" << this);
    
    auto pCodec = cym::CCodecManager::getCodec(mFile.ext());
    
    // @todo: this gets deleted after returns from ->decode(sys::spo<CCGeometryLoader>)
    
    pCodec->decode(pResourceLoader);
  }
  
  void TGeometryLoader<glm::cube>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TGeometryLoader<glm::SCube>::load(sys::spo<CResourceLoader>)");
    
// @todo: implement mDivisions
    
    auto    pGeometryLoader = sys::static_pointer_cast<TGeometryLoader<glm::SCube>>(pResourceLoader);
    const glm::SCube& rCube = pGeometryLoader->getCube();
    // geo buffer
    auto& rGeometryBuffer   = pGeometryLoader->getGeometryBuffer();
    // create positions, texcoords, normals
    auto& rPositions = rGeometryBuffer.getStream().make("positions", new cym::CPositionInput);
    auto& rTexcoords = rGeometryBuffer.getStream().make("texcoords", new cym::CTexcoordInput);
    auto& rNormals   = rGeometryBuffer.getStream().make("normals", new cym::CNormalInput);
    auto& rLayout    = rGeometryBuffer.getLayout();
    
    auto& rFlags {pGeometryLoader->mFlags};
          rFlags &= ~CGeometry::EFlag::CCW;
    
    static const uint kNumVertices {24};
    static const uint kNumIndices  {36};
    const glm::real hWidth  {rCube.length / 2.f};
    const glm::real hHeight {rCube.length / 2.f};
    const glm::real hDepth  {rCube.length / 2.f};
    
    rPositions.grow(kNumVertices);
    rPositions[ 0] = glm::vec3{-hWidth, -hHeight,  hDepth};
    rPositions[ 1] = glm::vec3{-hWidth, -hHeight,  hDepth};
    rPositions[ 2] = glm::vec3{-hWidth, -hHeight,  hDepth};
    rPositions[ 3] = glm::vec3{ hWidth, -hHeight,  hDepth};
    rPositions[ 4] = glm::vec3{ hWidth, -hHeight,  hDepth};
    rPositions[ 5] = glm::vec3{ hWidth, -hHeight,  hDepth};
    rPositions[ 6] = glm::vec3{ hWidth,  hHeight,  hDepth};
    rPositions[ 7] = glm::vec3{ hWidth,  hHeight,  hDepth};
    rPositions[ 8] = glm::vec3{ hWidth,  hHeight,  hDepth};
    rPositions[ 9] = glm::vec3{-hWidth,  hHeight,  hDepth};
    rPositions[10] = glm::vec3{-hWidth,  hHeight,  hDepth};
    rPositions[11] = glm::vec3{-hWidth,  hHeight,  hDepth};
    rPositions[12] = glm::vec3{-hWidth, -hHeight, -hDepth};
    rPositions[13] = glm::vec3{-hWidth, -hHeight, -hDepth};
    rPositions[14] = glm::vec3{-hWidth, -hHeight, -hDepth};
    rPositions[15] = glm::vec3{ hWidth, -hHeight, -hDepth};
    rPositions[16] = glm::vec3{ hWidth, -hHeight, -hDepth};
    rPositions[17] = glm::vec3{ hWidth, -hHeight, -hDepth};
    rPositions[18] = glm::vec3{ hWidth,  hHeight, -hDepth};
    rPositions[19] = glm::vec3{ hWidth,  hHeight, -hDepth};
    rPositions[20] = glm::vec3{ hWidth,  hHeight, -hDepth};
    rPositions[21] = glm::vec3{-hWidth,  hHeight, -hDepth};
    rPositions[22] = glm::vec3{-hWidth,  hHeight, -hDepth};
    rPositions[23] = glm::vec3{-hWidth,  hHeight, -hDepth};
    
    rTexcoords.grow(kNumVertices);
    rTexcoords[ 0] = glm::vec2{1.0f, 1.0f};
    rTexcoords[ 1] = glm::vec2{0.0f, 1.0f};
    rTexcoords[ 2] = glm::vec2{0.0f, 1.0f};
    rTexcoords[ 3] = glm::vec2{0.0f, 1.0f};
    rTexcoords[ 4] = glm::vec2{1.0f, 1.0f};
    rTexcoords[ 5] = glm::vec2{1.0f, 1.0f};
    rTexcoords[ 6] = glm::vec2{0.0f, 0.0f};
    rTexcoords[ 7] = glm::vec2{1.0f, 0.0f};
    rTexcoords[ 8] = glm::vec2{1.0f, 0.0f};
    rTexcoords[ 9] = glm::vec2{1.0f, 0.0f};
    rTexcoords[10] = glm::vec2{0.0f, 0.0f};
    rTexcoords[11] = glm::vec2{0.0f, 0.0f};
    rTexcoords[12] = glm::vec2{0.0f, 1.0f};
    rTexcoords[13] = glm::vec2{1.0f, 1.0f};
    rTexcoords[14] = glm::vec2{0.0f, 0.0f};
    rTexcoords[15] = glm::vec2{1.0f, 1.0f};
    rTexcoords[16] = glm::vec2{0.0f, 1.0f};
    rTexcoords[17] = glm::vec2{1.0f, 0.0f};
    rTexcoords[18] = glm::vec2{1.0f, 0.0f};
    rTexcoords[19] = glm::vec2{0.0f, 0.0f};
    rTexcoords[20] = glm::vec2{1.0f, 1.0f};
    rTexcoords[21] = glm::vec2{0.0f, 0.0f};
    rTexcoords[22] = glm::vec2{1.0f, 0.0f};
    rTexcoords[23] = glm::vec2{0.0f, 1.0f};
    
    rNormals.grow(kNumVertices);
    rNormals[ 0] = glm::vec3{ 0.0f,  0.0f,  1.0f};
    rNormals[ 1] = glm::vec3{-1.0f,  0.0f,  0.0f};
    rNormals[ 2] = glm::vec3{ 0.0f, -1.0f,  0.0f};
    rNormals[ 3] = glm::vec3{ 0.0f,  0.0f,  1.0f};
    rNormals[ 4] = glm::vec3{ 1.0f,  0.0f,  0.0f};
    rNormals[ 5] = glm::vec3{ 0.0f, -1.0f,  0.0f};
    rNormals[ 6] = glm::vec3{ 0.0f,  0.0f,  1.0f};
    rNormals[ 7] = glm::vec3{ 1.0f,  0.0f,  0.0f};
    rNormals[ 8] = glm::vec3{ 0.0f,  1.0f,  0.0f};
    rNormals[ 9] = glm::vec3{ 0.0f,  0.0f,  1.0f};
    rNormals[10] = glm::vec3{-1.0f,  0.0f,  0.0f};
    rNormals[11] = glm::vec3{ 0.0f,  1.0f,  0.0f};
    rNormals[12] = glm::vec3{ 0.0f,  0.0f, -1.0f};
    rNormals[13] = glm::vec3{-1.0f,  0.0f,  0.0f};
    rNormals[14] = glm::vec3{ 0.0f, -1.0f,  0.0f};
    rNormals[15] = glm::vec3{ 0.0f,  0.0f, -1.0f};
    rNormals[16] = glm::vec3{ 1.0f,  0.0f,  0.0f};
    rNormals[17] = glm::vec3{ 0.0f, -1.0f,  0.0f};
    rNormals[18] = glm::vec3{ 0.0f,  0.0f, -1.0f};
    rNormals[19] = glm::vec3{ 1.0f,  0.0f,  0.0f};
    rNormals[20] = glm::vec3{ 0.0f,  1.0f,  0.0f};
    rNormals[21] = glm::vec3{ 0.0f,  0.0f, -1.0f};
    rNormals[22] = glm::vec3{-1.0f,  0.0f,  0.0f};
    rNormals[23] = glm::vec3{ 0.0f,  1.0f,  0.0f};
    
    rLayout.push({
       3,  0,  9, // triangle 0  // face 0 // +z
       3,  9,  6, // triangle 1  // face 0
      12, 15, 18, // triangle 2  // face 1 // -z
      12, 18, 21, // triangle 3  // face 1
       1, 13, 22, // triangle 4  // face 2 // -x
       1, 22, 10, // triangle 5  // face 2
      16,  4,  7, // triangle 6  // face 3 // +x
      16,  7, 19, // triangle 7  // face 4 
       2,  5, 17, // triangle 8  // face 5 // -y
       2, 17, 14, // triangle 9  // face 5 
      23, 20,  8, // triangle 10 // face 6 // +y
      23,  8, 11  // triangle 11 // face 7
    });
    
    auto& rTangents  = rGeometryBuffer.getStream().make("tangents", new cym::CTangentInput);  rTangents.grow(kNumVertices);
    auto& rBinormals = rGeometryBuffer.getStream().make("binormals", new cym::CBinormalInput); rBinormals.grow(kNumVertices);
    auto& rIndices   = rLayout.indices();
    
    for(size_t i = 0; i < kNumIndices; i+=3) {
      ushort i0 = rIndices[i+0];
      ushort i1 = rIndices[i+1];
      ushort i2 = rIndices[i+2];

      glm::vec3& p0 {rPositions[i0]};
      glm::vec3& p1 {rPositions[i1]};
      glm::vec3& p2 {rPositions[i2]};
      
      glm::vec2& t0 {rTexcoords[i0]};
      glm::vec2& t1 {rTexcoords[i1]};
      glm::vec2& t2 {rTexcoords[i2]};
      
      glm::vec3 dp1 {p1 - p0}; // e1
      glm::vec3 dp2 {p2 - p0}; // e2
      
      glm::vec3 normal {glm::normalize(glm::cross(dp2, dp1))};
      rNormals[i0] += normal; // avarage the normals
      rNormals[i0]  = glm::normalize(rNormals[i0]);
      rNormals[i1] += normal;
      rNormals[i1]  = glm::normalize(rNormals[i1]);
      rNormals[i2] += normal;
      rNormals[i2]  = glm::normalize(rNormals[i2]);
      
      glm::vec2 dt1 {t1 - t0};
      glm::vec2 dt2 {t2 - t0};
      
      glm::real r {static_cast<glm::real>(1) / (dt1.x * dt2.y - dt1.y * dt2.x)};
      glm::vec3 ta {(dp1 * dt2.y - dp2 * dt1.y) * r};    // tangent
      glm::vec3 bi {(dp2 * dt1.x - dp1 * dt2.x) * r};    // binormal
      
      rTangents[i0] = ta;
      rTangents[i1] = ta;
      rTangents[i2] = ta;
      
      rBinormals[i0] = bi;
      rBinormals[i1] = bi;
      rBinormals[i2] = bi;
    }
    
// @todo: fix this, I think it crashes the app
    // if (mOptions & CGeometryLoader::INVERTED ) {
    //   for (size_t i = 0; i < kNumVertices; ++i) {
    //     rNormals[i]   *= -1.f;
    //     rTangents[i]  *= -1.f;
    //     rBinormals[i] *= -1.f;
    //   }
    //  
    //   for (uint i = 0; i < kNumIndices; i+=3) {
    //     uint tmp      = rIndices[i+1];
    //     rIndices[i+1] = rIndices[i+2];
    //     rIndices[i+2] = tmp;
    //   }
    // }
    
    auto& pMeshLoader = pGeometryLoader->getMeshLoader("cube");
    pMeshLoader->getRange().nStart = 0;
    pMeshLoader->getRange().nEnd   = rLayout.size();
  }
  
  void TGeometryLoader<glm::rect>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TGeometryLoader<glm::rect>::load(sys::spo<CResourceLoader>)");
    
    auto       pGeometryLoader = sys::static_pointer_cast<TGeometryLoader<glm::rect>>(pResourceLoader);
    glm::rect& rRect           = pGeometryLoader->geRectangle();
    
    auto& rGeometryBuffer = pGeometryLoader->getGeometryBuffer();
    
    auto& rPositions = rGeometryBuffer.getStream().make("positions", new cym::CPositionInput);
    auto& rTexcoords = rGeometryBuffer.getStream().make("texcoords", new cym::CTexcoordInput);
    auto& rNormals   = rGeometryBuffer.getStream().make("normals", new cym::CNormalInput);
    auto& rLayout    = rGeometryBuffer.getLayout();
  
    const uint  kDivisions {pGeometryLoader->mDivisions};
    auto&       rFlags {pGeometryLoader->mFlags};
                rFlags |= CGeometry::EFlag::CCW;
    const bool  bInverted {!!(rFlags & EFlag::INVERTED)};
    const bool  bTangents {!!(rFlags & EFlag::TANGENTS)};
    const bool  bNormals  {!!(rFlags & EFlag::NORMALS)};    // @todo
    const bool  bRepeatUV {!!(rFlags & EFlag::REPEATUV)};
    const float kTexScale {1.f};                              // @todo: on create
    const uint  kNumVertices {(kDivisions+1)*(kDivisions+1)}; // 4
    const uint  kNumIndices  {6 * kDivisions * kDivisions};
    const glm::real& fWidth  = rRect.width; 
    const glm::real& fHeight = rRect.height; 
    const glm::real  hWidth  = fWidth  / 2.f;
    const glm::real  hHeight = fHeight / 2.f;
  //const glm::real hDepth  = 0.f;
    const float fTexDiv = (bRepeatUV ? 1.f : (float)(kDivisions)) * kTexScale;
    
    const glm::vec3& vNormal = bInverted ? pGeometryLoader->mUp : pGeometryLoader->mUp *= -1.f;  
    
    rPositions.grow(kNumVertices);
    rTexcoords.grow(kNumVertices);
    rNormals.grow(kNumVertices);
    for (uint i = 0; i < kNumVertices; i++) {
      const uint nX = i % (kDivisions + 1); // 0 1 0 1
      const uint nZ = i / (kDivisions + 1); // 0 0 1 1
      
      rPositions[i] = glm::vec3{((float)(nX) / (float)(kDivisions)) * fWidth - hWidth,    // position.x 
                                0.f,                                                      // position.y
                                ((float)(nZ) / (float)(kDivisions)) * fHeight - hHeight}; // position.z
                                
      rTexcoords[i] = glm::vec2{(float)(nX) / fTexDiv,  // texcoord.s
                                (float)(nZ) / fTexDiv}; // texcoord.t
                                
      rNormals[i] = vNormal;
    }
    
    rLayout.grow(kNumIndices);
    for (uint i = 0, j = 0; i < kNumIndices; i+=6) {
      rLayout[i + 0] = j + kDivisions + 1 + (bInverted ? 0 : 1);
      rLayout[i + 1] = j + kDivisions + 1 + (bInverted ? 1 : 0);
      rLayout[i + 2] = j;
      rLayout[i + 3] = j + 1 + (bInverted ? kDivisions + 1 : 0);
      rLayout[i + 4] = j + 1 + (bInverted ? 0              : kDivisions + 1);
      rLayout[i + 5] = j;
      
      j = (j + 2) % (kDivisions + 1) ? j + 1 : j + 2;
    }
    
    if (bTangents) {
      auto& rTangents  = rGeometryBuffer.getStream().make("tangents", new cym::CTangentInput);
      auto& rBinormals = rGeometryBuffer.getStream().make("binormals", new cym::CBinormalInput);
      
      rTangents.grow(kNumVertices);
      rBinormals.grow(kNumVertices);
      
      for (ushort i = 0; i < kNumVertices; i++) {
        rTangents[i]  = glm::vec3{0.f};
        rBinormals[i] = glm::vec3{0.f};
      }
      
      for (uint i = 0; i < kNumIndices; i+=3) {
        const uint& i0 {rLayout[i+0]};
        const uint& i1 {rLayout[i+1]};
        const uint& i2 {rLayout[i+2]};
        
        const glm::vec3& p0 {rPositions[i0]};
        const glm::vec3& p1 {rPositions[i1]};
        const glm::vec3& p2 {rPositions[i2]};
        
        const glm::vec2& t0 {rTexcoords[i0]};
        const glm::vec2& t1 {rTexcoords[i1]};
        const glm::vec2& t2 {rTexcoords[i2]};
        
        const glm::vec3 dp1 {p1 - p0}; // edge 1 = 1 -> 0 = local x
        const glm::vec3 dp2 {p2 - p1}; // edge 2 = 2 -> 0 = local y
        
        const glm::vec2 dt1 {t1 - t0};
        const glm::vec2 dt2 {t2 - t1};
        
        const float     r  = 1.0f / (dt1.x * dt2.y - dt1.y * dt2.x);
        const glm::vec3 ta = (dp1 * dt2.y - dp2 * dt1.y) * r;         // tangent
        const glm::vec3 bi = (dp2 * dt1.x - dp1 * dt2.x) * r;         // binormal
        
        rTangents[i0] = ta;
        rTangents[i1] = ta;
        rTangents[i2] = ta;
        
        rBinormals[i0] = bi;
        rBinormals[i1] = bi;
        rBinormals[i2] = bi;
      }
      
      for (uint i = 0; i < kNumVertices; i++) {
        const glm::vec3& n {rNormals[i]};
        const glm::vec3& t {rTangents[i]};
        const glm::vec3& b {rBinormals[i]};
        
        rTangents[i] = glm::normalize(t - n * glm::dot(n,t));            // orthogonalize(Gram-Schmidt)
        rTangents[i] = glm::dot(glm::cross(n,t),b) < 0.f ? t * -1.f : t; // handedness
      }
    }
    
    auto& pMeshLoader = pGeometryLoader->getMeshLoader("rectangle");
    pMeshLoader->getRange().nStart = 0;
    pMeshLoader->getRange().nEnd   = rLayout.size();
  }
  
  void TGeometryLoader<glm::frustum>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TGeometryLoader<glm::frustum>::load(sys::spo<CResourceLoader>)");
    
    auto       pGeometryLoader = sys::static_pointer_cast<TGeometryLoader<glm::frustum>>(pResourceLoader);
    glm::frustum& rFrustum     = pGeometryLoader->getFrustum();
    
    auto& rGeometryBuffer      = pGeometryLoader->getGeometryBuffer();
    
    auto  tCorners {rFrustum.getCorners()};
    auto& tPlanes  {rFrustum.getPlanes()};
    
    // SYS_LOG_NFO("corners:" << tCorners);
    
    auto& rPositions = rGeometryBuffer.getStream().make("positions", new cym::CPositionInput);
    auto& rTexcoords = rGeometryBuffer.getStream().make("texcoords", new cym::CTexcoordInput);
    auto& rNormals   = rGeometryBuffer.getStream().make("normals", new cym::CNormalInput);
    auto& rLayout    = rGeometryBuffer.getLayout();
    
    const uint  kDivisions {pGeometryLoader->mDivisions};    // @todo: divisions
          uint& rFlags     {pGeometryLoader->mFlags};
                rFlags |= CGeometry::EFlag::CCW;
    const bool  bInverted  {!!(rFlags & EFlag::INVERTED)};   // @todo: inverted normals (and vertex order)
    const bool  bTangents  {!!(rFlags & EFlag::TANGENTS)};   // @todo: tangents
    const bool  bNormals   {!!(rFlags & EFlag::NORMALS)};    // @todo: normals
    const bool  bRepeatUV  {!!(rFlags & EFlag::REPEATUV)};
    
    const uint  kNumVertices {24}; // (kDivisions+1)*(kDivisions+1)}; // 4
    const uint  kNumIndices  {36}; // 6 * kDivisions * kDivisions};
    
    static const uint kNumPlanes {6};
    
    // static const uint kNumTriangles {2};
    // static const uint kTriangles[kNumPlanes * kNumTriangles][3] { 
    // /*L*/{glm::ECorner::LBN,glm::ECorner::LBF,glm::ECorner::LTF},
    //      {glm::ECorner::LBN,glm::ECorner::LTF,glm::ECorner::LTN},
    // /*R*/{glm::ECorner::RBN,glm::ECorner::RTN,glm::ECorner::RTF},
    //      {glm::ECorner::RBN,glm::ECorner::RTF,glm::ECorner::RBF},
    // /*B*/{glm::ECorner::LBN,glm::ECorner::RBN,glm::ECorner::RBF},
    //      {glm::ECorner::LBN,glm::ECorner::RBF,glm::ECorner::LBF},
    // /*T*/{glm::ECorner::LTN,glm::ECorner::LTF,glm::ECorner::RTF},
    //      {glm::ECorner::LTN,glm::ECorner::RTF,glm::ECorner::RTN},
    // /*F*/{glm::ECorner::LBF,glm::ECorner::RBF,glm::ECorner::RTF},
    //      {glm::ECorner::LBF,glm::ECorner::RTF,glm::ECorner::LTF},
    // /*N*/{glm::ECorner::LBN,glm::ECorner::LTN,glm::ECorner::RTN},
    //      {glm::ECorner::LBN,glm::ECorner::RTN,glm::ECorner::LTN}};
    
    // CCW order // LBN=0, RBN=1, LTN=2, RTN=3, LBF=4, RBF=5, LTF=6, RTF=7
    static const uint kVertices[kNumPlanes][4] = {
      /*L*/{glm::ECorner::LBN,glm::ECorner::LBF,glm::ECorner::LTF,glm::ECorner::LTN},
      /*R*/{glm::ECorner::RBF,glm::ECorner::RBN,glm::ECorner::RTN,glm::ECorner::RTF},
      /*B*/{glm::ECorner::LBN,glm::ECorner::RBN,glm::ECorner::RBF,glm::ECorner::LBF},
      /*T*/{glm::ECorner::LTF,glm::ECorner::RTF,glm::ECorner::RTN,glm::ECorner::LTN},
      /*F*/{glm::ECorner::LBF,glm::ECorner::RBF,glm::ECorner::RTF,glm::ECorner::LTF},
      /*N*/{glm::ECorner::RBN,glm::ECorner::LBN,glm::ECorner::LTN,glm::ECorner::RTN}};
    
    static const glm::real kTexcoords[4][2] { {0,0}, {1,0}, {1,1}, {0,1} };
    
    static const glm::real ONE {static_cast<glm::real>(1)};
    
    rPositions.grow(kNumVertices);
    rTexcoords.grow(kNumVertices);
    rNormals.grow(kNumVertices);
    // for each plane
    for (uint pi = 0, ii = 0, vi = 0; pi < kNumPlanes/*=6*/; pi++) {
      // for each corner in plane
      for (vi = 0; vi < 4; vi++, ii++) {
        // position
        rPositions[ii] = tCorners[kVertices[pi][vi]];
        // texcoord
        rTexcoords[ii] = kTexcoords[vi];
        // normal (from plane)
        rNormals[ii]   = tPlanes[pi].normal;
        rNormals[ii]  *= -glm::ONE;
      }
    }
    
    rLayout.grow(kNumIndices);
    // 36 = 6 faces * 2 triangles * 3 vertices
    for (uint ii = 0, ji = 0; ii < kNumIndices/*36*/; ii+=6/*faces*/, ji+=4/*vertices*/) {
      /* 24 (6faces * 4verts) vertices */
      rLayout[ii + 0] = ji + 0; 
      rLayout[ii + 1] = ji + 1;
      rLayout[ii + 2] = ji + 2;
      rLayout[ii + 3] = ji + 0;
      rLayout[ii + 4] = ji + 2;
      rLayout[ii + 5] = ji + 3;
    }
    
    auto& rTangents  = rGeometryBuffer.getStream().make("tangents", new cym::CTangentInput);  rTangents.grow(kNumVertices);
    auto& rBinormals = rGeometryBuffer.getStream().make("binormals", new cym::CBinormalInput); rBinormals.grow(kNumVertices);
    auto& rIndices   = rLayout.indices();
    // basically: for each triangle
    for(uint i = 0; i < kNumIndices; i+=3) {
      // index of each vertex of this triangle
      ushort i0 = rIndices[i+0];
      ushort i1 = rIndices[i+1];
      ushort i2 = rIndices[i+2];
      // positions for each vertex
      glm::vec3& p0 {rPositions[i0]}; //      /| p1
      glm::vec3& p1 {rPositions[i1]}; //     / |
      glm::vec3& p2 {rPositions[i2]}; // p0 /__| p2
      // texcoords for each vertex
      glm::vec2& t0 {rTexcoords[i0]}; // 0,1 +---+ 1,1
      glm::vec2& t1 {rTexcoords[i1]}; //     |   |
      glm::vec2& t2 {rTexcoords[i2]}; // 0,0 +---+ 1,0
      // edges from p0 -> p1 and from p0 -> p2
      glm::vec3 dp1 {p1 - p0}; // e1
      glm::vec3 dp2 {p2 - p0}; // e2
      // // compute normals (not needed there, we use the plane's normal)
      // glm::vec3 normal {glm::normalize(glm::cross(dp2, dp1))};
      // rNormals[i0] += normal; // avarage the normals
      // rNormals[i0]  = glm::normalize(rNormals[i0]);
      // rNormals[i1] += normal;
      // rNormals[i1]  = glm::normalize(rNormals[i1]);
      // rNormals[i2] += normal;
      // rNormals[i2]  = glm::normalize(rNormals[i2]);
      // tangent space edges
      glm::vec2 dt1 {t1 - t0};
      glm::vec2 dt2 {t2 - t0};
      
      glm::real r {ONE / (dt1.x * dt2.y - dt1.y * dt2.x)};
      glm::vec3 ta {(dp1 * dt2.y - dp2 * dt1.y) * r};    // tangent
      glm::vec3 bi {(dp2 * dt1.x - dp1 * dt2.x) * r};    // binormal
      
      rTangents[i0] = ta;
      rTangents[i1] = ta;
      rTangents[i2] = ta;
      
      rBinormals[i0] = bi;
      rBinormals[i1] = bi;
      rBinormals[i2] = bi;
    }
    
    auto& pMeshLoader = pGeometryLoader->getMeshLoader("frustum");
    pMeshLoader->getRange().nStart = 0;
    pMeshLoader->getRange().nEnd   = rLayout.size();
    
// @todo: check core/engine CCW vs CW settings to re-order vertices (if necessary) 
  }
}
