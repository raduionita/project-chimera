#include "cym/CModel.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  CMesh::~CMesh() {
    CYM_LOG_NFO("cym::CMesh::~CMesh()::" << this);
  }
  
  CModel::CModel(const cym::name& tName) : cym::CResource(tName) {
    CYM_LOG_NFO("cym::CModel::CModel(const cym::name&)::" << this);
  }
  
  CModel::CModel(sys::sptr<CModelLoader> pLoader) {
    CYM_LOG_NFO("cym::CModel::CModel(sys::sptr<CModelLoader>)::" << this);
    load(pLoader);
  }
  
  CModel::~CModel() {
     CYM_LOG_NFO("cym::CModel::~CModel()::" << this << " NAME:" << mName);
     //CModelManager::kill(this->mName);
  }
  
  void CModel::load(sys::sptr<CModelLoader> pLoader) {
    CYM_LOG_NFO("cym::CModel::load(sys::sptr<CModelLoader>)::" << this);
    
    cym::CGeometry& rGeometry = pLoader->mGeometry;
    
    rGeometry.pack();
    
    mVAO = new cym::CVertexArray;
    mIBO = new cym::CIndexBuffer{rGeometry.layout().data(), rGeometry.layout().size(), rGeometry.layout().count()};
    mVLO = new cym::CVertexLayout{cym::CVertexLayout::SEQUENTIAL};
    mVBO = new cym::CVertexBuffer{rGeometry.stream().size(), rGeometry.stream().count()};
  
// @todo merge geometries: CGeometry + CGeometry or rGeometry.concat(CGeometry) 

// @todo: CModelData could/should have an array of CGeometries

    // for (auto& rGeometry : rData.geometries) 
    for (auto&& [name,in] : rGeometry.inputs()) {
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
  
  void CModel::draw() { mVAO->bind(); mIBO->bind(); GLCALL(::glDrawElements(GL_TRIANGLES, mIBO->count(), GL_UNSIGNED_INT, GL_NULL)); }
  
  void CMesh::draw() { mModel->mVAO->bind(); mModel->mIBO->bind(); GLCALL(::glDrawElements(GL_TRIANGLES, mRange.getCount(), GL_UNSIGNED_INT, (void*)(mRange.getStart() * sizeof(int)))); }
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CModelManager::CModelManager()  { 
    CYM_LOG_NFO("cym::CModelManager::CModelManager()::" << this); 
  }
  
  CModelManager::~CModelManager() { 
    CYM_LOG_NFO("cym::CModelManager::~CModelManager()::" << this);
    //for (auto it = mModels.begin(); it != mModels.end(); )
      //CModelManager::kill(it->second);
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TModelLoader<sys::CFile>::load(sys::sptr<CResourceLoader> pResourceLoader) {
    CYM_LOG_NFO("cym::TModelLoader<sys::CFile>::load(sys::sptr<CResourceLoader>)::" << this);
    
    auto pCodec = cym::CCodecManager::getCodec(mFile.ext());
    
    // @todo: this gets deleted after returns from ->decode(sys::sptr<CModelLoader>)
    
    pCodec->decode(pResourceLoader);
  }
  
  void TModelLoader<glm::SCube>::load(sys::sptr<CResourceLoader> pResourceLoader) {
    CYM_LOG_NFO("cym::TModelLoader<glm::SCube>::load(sys::sptr<CResourceLoader>)");
    
    auto        pModelLoader = sys::static_pointer_cast<TModelLoader<glm::SCube>>(pResourceLoader);
    glm::SCube& rCube        = pModelLoader->getCube();
    
    auto& rGeometry    = pModelLoader->getGeometry();
    
    auto& rPositions = rGeometry.stream().make("positions", new cym::CPositionInput);
    auto& rTexcoords = rGeometry.stream().make("texcoords", new cym::CTexcoordInput);
    auto& rNormals   = rGeometry.stream().make("normals", new cym::CNormalInput);
    auto& rLayout    = rGeometry.layout();
    
    static const uint kNumVertices {24};
    static const uint kNumIndices  {36};
    const glm::real hWidth  = rCube.length / 2.f;
    const glm::real hHeight = rCube.length / 2.f;
    const glm::real hDepth  = rCube.length / 2.f;
    
    rPositions.grow(kNumVertices);
    rPositions[ 0] = glm::vec3(-hWidth, -hHeight,  hDepth);
    rPositions[ 1] = glm::vec3(-hWidth, -hHeight,  hDepth);
    rPositions[ 2] = glm::vec3(-hWidth, -hHeight,  hDepth);
    rPositions[ 3] = glm::vec3( hWidth, -hHeight,  hDepth);
    rPositions[ 4] = glm::vec3( hWidth, -hHeight,  hDepth);
    rPositions[ 5] = glm::vec3( hWidth, -hHeight,  hDepth);
    rPositions[ 6] = glm::vec3( hWidth,  hHeight,  hDepth);
    rPositions[ 7] = glm::vec3( hWidth,  hHeight,  hDepth);
    rPositions[ 8] = glm::vec3( hWidth,  hHeight,  hDepth);
    rPositions[ 9] = glm::vec3(-hWidth,  hHeight,  hDepth);
    rPositions[10] = glm::vec3(-hWidth,  hHeight,  hDepth);
    rPositions[11] = glm::vec3(-hWidth,  hHeight,  hDepth);
    rPositions[12] = glm::vec3(-hWidth, -hHeight, -hDepth);
    rPositions[13] = glm::vec3(-hWidth, -hHeight, -hDepth);
    rPositions[14] = glm::vec3(-hWidth, -hHeight, -hDepth);
    rPositions[15] = glm::vec3( hWidth, -hHeight, -hDepth);
    rPositions[16] = glm::vec3( hWidth, -hHeight, -hDepth);
    rPositions[17] = glm::vec3( hWidth, -hHeight, -hDepth);
    rPositions[18] = glm::vec3( hWidth,  hHeight, -hDepth);
    rPositions[19] = glm::vec3( hWidth,  hHeight, -hDepth);
    rPositions[20] = glm::vec3( hWidth,  hHeight, -hDepth);
    rPositions[21] = glm::vec3(-hWidth,  hHeight, -hDepth);
    rPositions[22] = glm::vec3(-hWidth,  hHeight, -hDepth);
    rPositions[23] = glm::vec3(-hWidth,  hHeight, -hDepth);
    
    rTexcoords.grow(kNumVertices);
    rTexcoords[ 0] = glm::vec2(1.0f, 1.0f);
    rTexcoords[ 1] = glm::vec2(0.0f, 1.0f);
    rTexcoords[ 2] = glm::vec2(0.0f, 1.0f);
    rTexcoords[ 3] = glm::vec2(0.0f, 1.0f);
    rTexcoords[ 4] = glm::vec2(1.0f, 1.0f);
    rTexcoords[ 5] = glm::vec2(1.0f, 1.0f);
    rTexcoords[ 6] = glm::vec2(0.0f, 0.0f);
    rTexcoords[ 7] = glm::vec2(1.0f, 0.0f);
    rTexcoords[ 8] = glm::vec2(1.0f, 0.0f);
    rTexcoords[ 9] = glm::vec2(1.0f, 0.0f);
    rTexcoords[10] = glm::vec2(0.0f, 0.0f);
    rTexcoords[11] = glm::vec2(0.0f, 0.0f);
    rTexcoords[12] = glm::vec2(0.0f, 1.0f);
    rTexcoords[13] = glm::vec2(1.0f, 1.0f);
    rTexcoords[14] = glm::vec2(0.0f, 0.0f);
    rTexcoords[15] = glm::vec2(1.0f, 1.0f);
    rTexcoords[16] = glm::vec2(0.0f, 1.0f);
    rTexcoords[17] = glm::vec2(1.0f, 0.0f);
    rTexcoords[18] = glm::vec2(1.0f, 0.0f);
    rTexcoords[19] = glm::vec2(0.0f, 0.0f);
    rTexcoords[20] = glm::vec2(1.0f, 1.0f);
    rTexcoords[21] = glm::vec2(0.0f, 0.0f);
    rTexcoords[22] = glm::vec2(1.0f, 0.0f);
    rTexcoords[23] = glm::vec2(0.0f, 1.0f);
    
    rNormals.grow(kNumVertices);
    rNormals[ 0] = glm::vec3( 0.0f,  0.0f,  1.0f);
    rNormals[ 1] = glm::vec3(-1.0f,  0.0f,  0.0f);
    rNormals[ 2] = glm::vec3( 0.0f, -1.0f,  0.0f);
    rNormals[ 3] = glm::vec3( 0.0f,  0.0f,  1.0f);
    rNormals[ 4] = glm::vec3( 1.0f,  0.0f,  0.0f);
    rNormals[ 5] = glm::vec3( 0.0f, -1.0f,  0.0f);
    rNormals[ 6] = glm::vec3( 0.0f,  0.0f,  1.0f);
    rNormals[ 7] = glm::vec3( 1.0f,  0.0f,  0.0f);
    rNormals[ 8] = glm::vec3( 0.0f,  1.0f,  0.0f);
    rNormals[ 9] = glm::vec3( 0.0f,  0.0f,  1.0f);
    rNormals[10] = glm::vec3(-1.0f,  0.0f,  0.0f);
    rNormals[11] = glm::vec3( 0.0f,  1.0f,  0.0f);
    rNormals[12] = glm::vec3( 0.0f,  0.0f, -1.0f);
    rNormals[13] = glm::vec3(-1.0f,  0.0f,  0.0f);
    rNormals[14] = glm::vec3( 0.0f, -1.0f,  0.0f);
    rNormals[15] = glm::vec3( 0.0f,  0.0f, -1.0f);
    rNormals[16] = glm::vec3( 1.0f,  0.0f,  0.0f);
    rNormals[17] = glm::vec3( 0.0f, -1.0f,  0.0f);
    rNormals[18] = glm::vec3( 0.0f,  0.0f, -1.0f);
    rNormals[19] = glm::vec3( 1.0f,  0.0f,  0.0f);
    rNormals[20] = glm::vec3( 0.0f,  1.0f,  0.0f);
    rNormals[21] = glm::vec3( 0.0f,  0.0f, -1.0f);
    rNormals[22] = glm::vec3(-1.0f,  0.0f,  0.0f);
    rNormals[23] = glm::vec3( 0.0f,  1.0f,  0.0f);
    
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
    
    auto& rTangents  = rGeometry.stream().make("tangents", new cym::CTangentInput);  rTangents.grow(kNumVertices);
    auto& rBinormals = rGeometry.stream().make("binormals", new cym::CBinormalInput); rBinormals.grow(kNumVertices);
    auto& rIndices   = rLayout.indices();
    
    for(size_t i = 0; i < kNumIndices; i+=3) {
      ushort i0 = rIndices[i+0];
      ushort i1 = rIndices[i+1];
      ushort i2 = rIndices[i+2];

      glm::vec3& p0 = rPositions[i0];
      glm::vec3& p1 = rPositions[i1];
      glm::vec3& p2 = rPositions[i2];
      
      glm::vec2& t0 = rTexcoords[i0];
      glm::vec2& t1 = rTexcoords[i1];
      glm::vec2& t2 = rTexcoords[i2];
      
      glm::vec3 dp1(p1 - p0); // e1
      glm::vec3 dp2(p2 - p0); // e2
      
      glm::vec3 normal = glm::normalize(glm::cross(dp2, dp1));
      rNormals[i0] += normal; // avarage the normals
      rNormals[i0]  = glm::normalize(rNormals[i0]);
      rNormals[i1] += normal;
      rNormals[i1]  = glm::normalize(rNormals[i1]);
      rNormals[i2] += normal;
      rNormals[i2]  = glm::normalize(rNormals[i2]);
      
      glm::vec2 dt1 = t1 - t0;
      glm::vec2 dt2 = t2 - t0;
      
      float r = 1.0f / (dt1.x * dt2.y - dt1.y * dt2.x);
      glm::vec3 ta = (dp1 * dt2.y - dp2 * dt1.y) * r;    // tangent
      glm::vec3 bi = (dp2 * dt1.x - dp1 * dt2.x) * r;    // binormal
      
      rTangents[i0] = ta;
      rTangents[i1] = ta;
      rTangents[i2] = ta;
      
      rBinormals[i0] = bi;
      rBinormals[i1] = bi;
      rBinormals[i2] = bi;
    }
    
    // @todo: fix this, I think it crashes the app
    // if (mOptions & CModelLoader::INVERTED ) {
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
    
    auto& pMeshLoader = pModelLoader->getMeshLoader("cube");
    pMeshLoader->getRange().nStart = 0;
    pMeshLoader->getRange().nEnd   = rLayout.size();
  }
  
  void TModelLoader<glm::rect>::load(sys::sptr<CResourceLoader> pResourceLoader) {
    CYM_LOG_NFO("cym::TModelLoader<glm::rect>::load(sys::sptr<CResourceLoader>)");
    
    auto       pModelLoader = sys::static_pointer_cast<TModelLoader<glm::rect>>(pResourceLoader);
    glm::rect& rRect        = pModelLoader->geRectangle();
    
    auto& rGeometry    = pModelLoader->getGeometry();
    
    auto& rPositions = rGeometry.stream().make("positions", new cym::CPositionInput);
    auto& rTexcoords = rGeometry.stream().make("texcoords", new cym::CTexcoordInput);
    auto& rNormals   = rGeometry.stream().make("normals", new cym::CNormalInput);
    auto& rLayout    = rGeometry.layout();
  
    const uint  kDivisions {pModelLoader->mDivisions};
    const uint  kFlags {pModelLoader->mFlags};
    const bool  bInverted {!!(kFlags & EFlag::INVERTED)};
    const bool  bTangents {!!(kFlags & EFlag::TANGENTS)};
    const bool  bNormals  {!!(kFlags & EFlag::NORMALS)};    // @todo
    const bool  bRepeatUV {!!(kFlags & EFlag::REPEATUV)};
    const float kTexScale {1.f};                              // @todo: on create
    const uint  kNumVertices {(kDivisions+1)*(kDivisions+1)}; // 4
    const uint  kNumIndices  {6 * kDivisions * kDivisions};
    const glm::real& fWidth  = rRect.width; 
    const glm::real& fHeight = rRect.height; 
    const glm::real hWidth  = fWidth  / 2.f;
    const glm::real hHeight = fHeight / 2.f;
  //const glm::real hDepth  = 0.f;
    const float fTexDiv = (bRepeatUV ? 1.f : (float)(kDivisions)) * kTexScale;
    
    const glm::vec3& vNormal = bInverted ? pModelLoader->mUp : pModelLoader->mUp *= -1.f;  
    
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
      auto& rTangents  = rGeometry.stream().make("tangents", new cym::CTangentInput);
      auto& rBinormals = rGeometry.stream().make("binormals", new cym::CBinormalInput);
      
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
        const glm::vec3& n = rNormals[i];
        const glm::vec3& t = rTangents[i];
        const glm::vec3& b = rBinormals[i];
        
        rTangents[i] = glm::normalize(t - n * glm::dot(n,t));            // orthogonalize(Gram-Schmidt)
        rTangents[i] = glm::dot(glm::cross(n,t),b) < 0.f ? t * -1.f : t; // handedness
      }
    }
    
    auto& pMeshLoader = pModelLoader->getMeshLoader("rectangle");
    pMeshLoader->getRange().nStart = 0;
    pMeshLoader->getRange().nEnd   = rLayout.size();
  }
  
  
  void TModelLoader<glm::frustum>::load(sys::sptr<CResourceLoader> pResourceLoader) {
    CYM_LOG_NFO("cym::TModelLoader<glm::frustum>::load(sys::sptr<CResourceLoader>)");
    
    auto          pModelLoader = sys::static_pointer_cast<TModelLoader<glm::frustum>>(pResourceLoader);
    glm::frustum& rFrustum     = pModelLoader->getFrustum();
    
    auto& rGeometry    = pModelLoader->getGeometry();
    
// get 
    
    
    
    
    
    
    
    
  }
}
