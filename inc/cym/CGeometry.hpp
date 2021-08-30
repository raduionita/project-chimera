#ifndef __cym_cgeometry_hpp__
#define __cym_cgeometry_hpp__

#include "sys/TPointer.hpp"
#include "sys/TSingleton.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/CTask.hpp"
#include "sys/TBlock.hpp"
#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CSkeleton.hpp"
#include "cym/CCollider.hpp"
#include "cym/CVertexArray.hpp"
#include "cym/CDataBuffer.hpp"
#include "cym/CVertexLayout.hpp"
#include "cym/CDrawable.hpp"
#include "cym/TInstance.hpp"
#include "glm/CAABB.hpp"
#include "glm/CFrustum.hpp"
#include "glm/CVector.hpp"

#include <algorithm>
#include <unordered_map>

namespace cym {
  class CGeometry; typedef sys::ptr<CGeometry> PGeometry;
  class CMesh;     typedef sys::ptr<CMesh>     PMesh;
  
  class CGeometryLoader; template<typename T> class TGeometryLoader; typedef sys::ptr<CGeometryLoader> PGeometryLoader;
  class CMeshLoader;     template<typename T> class TMeshLoader;     typedef sys::ptr<CMeshLoader>     PMeshLoader;
  
  class CGeometryManager;
  
  // buffer //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CGeometryBuffer;
  
  class CGeometryInput {
      friend class CGeometryBuffer;
    public:
      typedef EVertexAttribute EAttribute; 
      typedef uint32_t         count_t;
    public:
      CGeometryInput() = default;
      virtual ~CGeometryInput() = default;
    public:
      virtual inline EAttribute  attribute() const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_t     stride()    const { throw sys::exception("NOT IMPLEMENTED", __FILE__, __LINE__); }
      virtual inline count_t     size()      const { throw sys::exception("NOT IMPLEMENTED", __FILE__, __LINE__); }
      virtual inline bool        empty()     const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_t     count()     const { throw sys::exception("NOT IMPLEMENTED", __FILE__, __LINE__); }
      virtual inline const void* data()      const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline GLenum      type()      const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_t     width()     const { throw sys::exception("NOT IMPLEMENTED", __FILE__, __LINE__); }
      virtual inline void        push(const void*) { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
  };
  
  template<typename T, CGeometryInput::EAttribute A, GLenum E, uint W> class TGeometryInput : public CGeometryInput {
      friend class CGeometryBuffer;
    public:
      typedef CGeometryInput::EAttribute EAttribute; 
      typedef T                          value_t;
      typedef std::vector<T>             input_t;
    protected:
      std::vector<T> mValues;
    public: // ctors
      using CGeometryInput::CGeometryInput;
    public: // operators
      value_t& operator [](count_t i) { assert(i < mValues.size() && "out of bounds"); return mValues[i]; }
      void     operator +=(T&& v)     { mValues.push_back(std::move(v)); }
    public: // cats
      operator       T*()       { return static_cast<T*>(mValues.data()); }
      operator const T*() const { return static_cast<const T*>(mValues.data()); }
    public: // get/setters
      virtual inline EAttribute            attribute() const   override { return A; }
      virtual inline count_t               stride()    const   override { return sizeof(T); }
      virtual inline count_t               size()      const   override { return mValues.size() * sizeof(T); }
      virtual inline bool                  empty()     const   override { return mValues.size() == 0; }
      virtual inline count_t               count()     const   override { return mValues.size(); }
      virtual inline const void*           data()      const   override { return static_cast<const void*>(mValues.data()); }
      virtual inline GLenum                type()      const   override { return E; }
      virtual inline count_t               width()     const   override { return W; }
              inline const std::vector<T>& values()    const            { return mValues; }
    public: // actions
      virtual inline void                  push(const void* v) override { const T* p = static_cast<const T*>(v); mValues.push_back(*p); }
              inline void                  push(T&& v)                  { mValues.push_back(std::move(v)); }
              inline void                  push(const T& v)             { mValues.push_back(v); }
              inline T&                    next()                       { return mValues.emplace_back(T{}); }
              inline void                  grow(count_t n)              { mValues.resize(n); }
  };
  
  class CGeometryStream {
      friend class CGeometry;
      friend class CGeometryBuffer;
    public:
      typedef CGeometryInput::count_t count_type;
    protected:
      std::map<sys::string,CGeometryInput*> mInputs; // positions, normals, texcoords, texcoords2 (multi material), binormals...
    public:
      virtual ~CGeometryStream() { for (auto& in : mInputs) delete in.second; }
    public:
      CGeometryInput* operator[](const sys::string& name) { auto it = mInputs.find(name); if (it != mInputs.end()) return it->second; throw sys::exception("Input "+ name + " NOT FOUND!",__FILE__,__LINE__); }
    public: // actions
      /* stream.find("position") => CGeometryInput*|CPositonInput* */
      const CGeometryInput* const find(const sys::string& name) const { auto it = mInputs.find(name); if (it != mInputs.end()) return it->second; return nullptr; }
      /* stream.make("position", CPositionInput) => CPositionInput* */
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CGeometryInput*>::value>::type> T& make(sys::string&& name, T*&& in)  { mInputs.insert({std::move(name), std::move(in)}); return *in; }
      /* stream.pack() pack the stream, reduce empty inputs */
      inline               void       pack()           { 
        for (auto it = mInputs.begin(); it != mInputs.end(); ) {
          if (it->second == nullptr || it->second->empty()) {
            delete it->second;
            mInputs.erase(it++);
          } else {
            ++it;
          }
        }
      }
    public: // getters
      /*  uint32_t // an input's data pices count  */
      inline               count_type count() const    { return mInputs.begin()->second->count(); }
      inline               count_type size()  const    { count_type s = 0; for (auto& in : mInputs) s += in.second->size(); return s; }
  };
  
  class CGeometryLayout {
      friend class CGeometryBuffer;
    public:
      typedef uint32_t                value_type;
      typedef CGeometryInput::count_t count_type;
    protected:
      std::vector<value_type> mIndices; // int[] // int array
    public:
      value_type& operator[](count_type i)  { assert(i < mIndices.size() && "out of bounds"); return mIndices[i]; }
    public:
      operator const value_type*() const { return static_cast<const value_type*>(mIndices.data()); }
      operator const void*()       const { return static_cast<const void*>(mIndices.data()); }
    public:
      inline std::vector<value_type>& indices() { return mIndices; }
      inline count_type  count() const      { return mIndices.size(); }
      inline count_type  size()  const      { return mIndices.size() * sizeof(value_type); }
      inline void        push(value_type v) { mIndices.push_back(v); }
      inline void push(const std::initializer_list<value_type>& tValues) { mIndices.reserve(mIndices.size() + tValues.size()); std::copy(tValues.begin(), tValues.end(), std::back_inserter(mIndices)); }
      inline const void* data()  const      { return static_cast<const void*>(mIndices.data()); }
      inline void        grow(count_type n) { mIndices.resize(n); }
  };
  
  class CGeometryBuffer {
      friend class CGeometry;
      friend class CGeometryLoader;
    protected:
      CGeometryStream mStream;
      CGeometryLayout mLayout;
    public: // getters
      /* [vbo] geometry stream (= holds all inputs) */
      inline CGeometryStream&                     getStream()  { return mStream; }
      /* [vbo] get inputs vector (from inside geometry stream) */
      inline decltype(CGeometryStream::mInputs)&  getInputs()  { return mStream.mInputs; }
      /* [ibo] geometry layoyt */
      inline CGeometryLayout&                     getLayout()  { return mLayout; }
      /* [ibo] get indices vecort (from insider geometry layout) */
      inline decltype(CGeometryLayout::mIndices)& getIndices() { return mLayout.mIndices; }
    public: // actions
      /* buffer.pack() pack all geometry stream inputs */
      inline void                                 pack()    { mStream.pack(); }
      /* buffer.make() make new input inside geometry stream */
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CGeometryInput*>::value>::type> T& make(std::string&& name, T*&& in) { return mStream.make(std::move(name),
                                                                                                                                                                             std::move(in)); }
  };
  
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::POSITION,GL_FLOAT,3> CPositionInput;  // float[3][n] // vec3[n]
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::NORMAL,  GL_FLOAT,3> CNormalInput;
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::COLOR,   GL_FLOAT,3> CColorInput;
  typedef TGeometryInput<glm::vec2, CGeometryInput::EAttribute::TEXCOORD,GL_FLOAT,2> CTexcoordInput;
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::TANGENT, GL_FLOAT,3> CTangentInput;
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::BINORMAL,GL_FLOAT,3> CBinormalInput;
  typedef TGeometryInput<glm::uvec3,CGeometryInput::EAttribute::JOINTS,  GL_UINT, 3> CJointsInput;    // uint[3][n]
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::WEIGHTS, GL_FLOAT,3> CWeightsInput;
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMesh : public cym::CResource, public cym::CDrawable {
      friend class CGeometry;
      friend class CMeshLoader;
      friend class CMeshManager;
      friend class CGeometryLoader;
      friend class CGeometryManager;
    public:
      typedef sys::string name_type;
    protected:
      cym::PMaterial    mMaterial;
      bool              mHidden    {false};
      cym::EPrimitive   mPrimitive {cym::EPrimitive::TRIANGLES};
      cym::CBufferRange mRange;
      // cym::PGeometry    mGeometry;
    public:
      using cym::CResource::CResource;
      CMesh(const std::string& tName);
      ~CMesh();
    public:
      inline bool hasMaterial() const                { return mMaterial != nullptr; }
      inline void setMaterial(decltype(mMaterial) m) { mMaterial = m; }
      inline void setRange(const CBufferRange& r)    { mRange = r; }
      inline const cym::CBufferRange& getRange() const { return mRange; }
      inline void setHidden(bool b = true)           { mHidden = b; }
      inline bool isHidden()                         { return mHidden; }
      inline cym::EPrimitive getPrimitive() const { return mPrimitive; }
    public:
      inline virtual void draw() { }
  };
  
  class CGeometry : public cym::CResource, public cym::CDrawable {
      friend class CMesh;
      friend class CGeometryManager;
    public:
      enum EFlag {
        FLAG       = 1, // 1 << 0
        POSITIONS  = FLAG << 1,
        TEXCOORDS  = FLAG << 2,
        NORMALS    = FLAG << 3,
        TANGENTS   = FLAG << 4,
        BINORMALS  = FLAG << 5,
        VERTICES   = POSITIONS | TEXCOORDS | NORMALS | TANGENTS | BINORMALS,
        MATERIALS  = FLAG << 7,
        TEXTURES   = FLAG << 8,
        SKELETON   = FLAG << 9,
        ANIMATIONS = FLAG << 10 | SKELETON,
        
        DEFAULT    = FLAG | VERTICES | MATERIALS | TEXTURES | ANIMATIONS,
        
        NORMALIZED = FLAG << 11,             // normalize position vectors | must have position
        INVERTED   = FLAG << 12 | NORMALS ,  // invert normals | must have normals
        REPEATUV   = FLAG << 13,             
        FLATFACE   = FLAG << 14,             // flat face - for loaded meshes this will used default normals - otherwise compute face normals
        
        FLIPXY     = FLAG << 15,
        FLIPYZ     = FLAG << 16,
        FLIPXZ     = FLAG << 17,
        
        CCW        = FLAG << 18,
      };
    private:
      sys::ptr<CVertexArray>  mVAO;
      sys::ptr<CVertexBuffer> mVBO;
      sys::ptr<CIndexBuffer>  mIBO;
      sys::ptr<CVertexLayout> mVLO;
    protected:
      uint                        mFlags {EFlag::CCW};
      sys::map<sys::string,PMesh> mMeshes;
      glm::aabb                   mAABB;
// @todo: mSkeleton // sys::ptr<CSkeleton>                        mSkeleton {new CSkeleton};
// @todo: mAnimator // animations list wrapper // this should be common among other similar (skeleton) models
    public: // ctors
      using cym::CResource::CResource;
      CGeometry(const sys::string& tName = "");
      ~CGeometry();
    public: // operators
      inline PMesh& operator [](uint i)               { return getMesh(i); }
      inline PMesh& operator [](const sys::string& n) { return getMesh(n); }
    public: // get/setters
      inline size_t           getCount() const { return mMeshes.size(); }
      inline const sys::map<sys::string,PMesh>& getMeshes() const { return mMeshes; }
      inline void             addMesh(PMesh pMesh)             { /* pMesh->mGeometry = this; */ auto it {mMeshes.find(pMesh->mName)}; if (it == mMeshes.end()) { mMeshes.insert(std::pair(pMesh->mName, pMesh)); } }
      inline PMesh&           getMesh(const sys::string& name) { return mMeshes[name]; }
      inline PMesh&           getMesh(uint i)                  { assert(i < mMeshes.size()); for (auto it = mMeshes.begin(); it != mMeshes.end(); ++it, i--) if (i == 0) return it->second; throw sys::exception("OUT OF BOUNDS", __FILE__, __LINE__); }
      inline uint             getFlags() const                 { return mFlags; }
      inline const glm::aabb& getAABB() const                  { return mAABB; }
    public: // actions
      inline  void bind() { mVAO->bind(); mIBO->bind(); }
      virtual void draw() override;
  };

  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMeshLoader : public CResourceLoader {
      friend class CMesh;
      friend class CGeometry;
      friend class CMeshManager;
      friend class CGeometryLoader;
      friend class CGeometryManager;
      typedef struct { uint nStart, nEnd; } range_type;
    protected:
      bool            mHidden {false};
      cym::EPrimitive mPrimitive {cym::EPrimitive::TRIANGLES};
      range_type      mRange;
      PMaterialLoader mMaterialLoader;
    public:
      using cym::CResourceLoader::CResourceLoader;
    public:
      inline virtual void load(PMesh) { SYS_LOG_NFO("cym::CMeshLoader::load(PMesh)::" << this); }
    public:
      inline decltype(mMaterialLoader)& getMaterialLoader() { if (!mMaterialLoader) mMaterialLoader = new CMaterialLoader; return mMaterialLoader; }
      inline decltype(mMaterialLoader)& useMaterialLoader(const std::string& tName) { if (!mMaterialLoader) mMaterialLoader = new CMaterialLoader{tName}; else mMaterialLoader->getName() = tName; return mMaterialLoader; }
      inline void                       setMaterialLoader(sys::ptr<CMaterialLoader> pLoader) { mMaterialLoader = pLoader; }
      inline range_type&                getRange() { return mRange; }
      inline void                       setRange(uint tStart, uint tEnd) { mRange.nStart = tStart; mRange.nEnd = tEnd; }
      inline void                       setRangeStart(uint tStart) { mRange.nStart = tStart; }
      inline void                       setRangeEnd(uint tEnd) { mRange.nEnd = tEnd; }
      inline void                       setPrimitive(const cym::EPrimitive ep) { mPrimitive = ep; }
      inline void                       setHidden(bool b = true) { mHidden = b; }
  };
  
  class CGeometryLoader : public CResourceLoader {
      friend class CGeometry;
      friend class CGeometryManager;
      typedef std::map<std::string,PMeshLoader> mesh_map;
    public:
      using EFlag = CGeometry::EFlag;
    protected:
      uint                              mFlags {EFlag::CCW};
      cym::CGeometryBuffer              mGeometryBuffer;
      std::map<std::string,PMeshLoader> mMeshLoaders;
    public:
      using CResourceLoader::CResourceLoader;
      inline CGeometryLoader(const sys::string& tName, uint eFlags = EFlag::DEFAULT) : CResourceLoader(tName), mFlags{eFlags} { SYS_LOG_NFO("cym::CGeometryLoader::CGeometryLoader(sys::string&,ushort)::" << this);  }
      inline ~CGeometryLoader() { SYS_LOG_NFO("cym::CGeometryLoader::~CGeometryLoader()::" << this); }
    public:
      inline virtual void load(PGeometry) { SYS_LOG_NFO("cym::CGeometryLoader::load(PGeometry)::" << this); }
    public:
      inline uint                   getFlags()                              { return mFlags; }
      inline bool                   hasFlag(EFlag e)                        { return mFlags & e; }
      inline bool                   hasFlags(uint es)                       { return mFlags & es; }
      inline cym::CGeometryBuffer&  getGeometryBuffer()                     { return mGeometryBuffer; }
      inline mesh_map&              getMeshLoaders()                        { return mMeshLoaders; }
      inline PMeshLoader&           getMeshLoader(const std::string& tName) { auto& pLoader = mMeshLoaders[tName]; if (!pLoader) pLoader = new CMeshLoader{tName}; return pLoader; }
      inline PMeshLoader&           newMeshLoader(const std::string& tName) { auto& pLoader = mMeshLoaders[tName]; pLoader = new CMeshLoader{tName}; return pLoader; }
    public:
      template<typename T> inline static sys::ptr<TGeometryLoader<T>> from(const T& tSource) { return new TGeometryLoader<T>{tSource}; }
      template<typename T, typename... Args> inline static sys::string name(const T& tSource, Args&&... args) { return TGeometryLoader<T>::name(tSource, std::forward<Args>(args)...); }
    public:
      inline decltype(cym::CGeometryBuffer::mStream)& getStream() { return mGeometryBuffer.mStream; }
      inline decltype(cym::CGeometryBuffer::mLayout)& getLayout() { return mGeometryBuffer.mLayout; }
  };
  
  template<typename T> class TGeometryLoader : public CGeometryLoader { };
  
  template<> class TGeometryLoader<sys::file> : public CGeometryLoader {
      friend class CGeometryCodec;
    protected:
      sys::CFile mFile;
    public:
      inline TGeometryLoader(const sys::CFile& tFile, uint eFlags = EFlag::DEFAULT) : CGeometryLoader(tFile.path(), eFlags), mFile{tFile} { };
    public:
      inline static sys::string name(const sys::file& tFile) { return tFile.path(); }
      virtual void load(PGeometry) override;
    public:
      inline sys::file& getFile() { return mFile; }
  };
  
  template<> class TGeometryLoader<glm::cube> : public CGeometryLoader {
    protected:
      glm::SCube mCube;
      uint       mXDivisions {1u};
      uint       mYDivisions {1u};
      uint       mZDivisions {1u};
    public:
      inline TGeometryLoader(const glm::SCube& tCube, uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tCube, 1u, 1u, 1u), eFlags), mCube(tCube) { }
      inline TGeometryLoader(const glm::SCube& tCube, uint nD, uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tCube, nD, nD, nD), eFlags), mCube{tCube}, mXDivisions{nD}, mYDivisions{nD}, mZDivisions{nD} { }
      inline TGeometryLoader(const glm::SCube& tCube, uint nXD, uint nYD, uint nZD, uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tCube, nXD, nYD, nZD), eFlags), mCube{tCube}, mXDivisions{nXD}, mYDivisions{nYD}, mZDivisions{nZD} { }
    public:
      inline static sys::string name(const glm::SCube& tCube, uint nXD = 1u, uint nYD = 1u, uint nZD = 1u) { return std::string("cube:")+sys::to_string(tCube.length,3)+"|"+std::to_string(nXD)+"x"+std::to_string(nYD)+"x"+std::to_string(nZD); }
      virtual void load(PGeometry) override;
    public:
      inline glm::SCube& getCube() { return mCube; }
  };
  
  template<> class TGeometryLoader<glm::rect> : public CGeometryLoader {
    protected:
      glm::rect mRectangle;
      uint      mDivisions  {1u};
      glm::vec3 mUp         {glm::Y}; // @todo
    public:
      inline TGeometryLoader(const glm::rect& tRect, uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tRect, 1u, glm::Y), eFlags), mRectangle(tRect) { }
      inline TGeometryLoader(const glm::rect& tRect, uint nDivisions, const glm::vec3& vUp, uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tRect, nDivisions, vUp), eFlags), mRectangle{tRect}, mDivisions{nDivisions}, mUp{vUp} { }
    public:
      inline static sys::string name(const glm::rect& tRect, uint nDivisions = 1u, const glm::vec3& vAxis = glm::Y, uint eFlags = EFlag::DEFAULT) { return std::string("rect:") + sys::to_string(tRect.width, 3) + 'x' + sys::to_string(tRect.height, 3) + '|' + std::to_string(nDivisions) + '|' + sys::to_string(vAxis, 1); }
      virtual void load(PGeometry) override;
    public:
      inline glm::rect& geRectangle() { return mRectangle; }
  };
  
  template<> class TGeometryLoader<glm::frustum> : public CGeometryLoader {
    protected:
      glm::frustum mFrustum; // use planes normal as the up vector
      glm::uint    mDivisions {1u};
    public:
      inline TGeometryLoader(const glm::frustum& tFrustum, cym::uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tFrustum, 1u), eFlags), mFrustum{tFrustum} { }
      inline TGeometryLoader(const glm::frustum& tFrustum, const uint nDivisions, const uint eFlags = EFlag::DEFAULT) : CGeometryLoader(name(tFrustum, nDivisions), eFlags), mFrustum{tFrustum}, mDivisions{nDivisions} { }
    public:
      inline static sys::string name(const glm::frustum& f, const glm::uint d=1u, uint e=EFlag::DEFAULT) { return std::string("frustum:") +'|'+ sys::to_string(d); }
      virtual void load(PGeometry) override;
    public:
      inline glm::frustum& getFrustum() { return mFrustum; }
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: CAnimatorManager
// @todo: CAnimationManager
  
  class CMeshManager : public cym::TResourceManager<CMesh>, public sys::TSingleton<CMeshManager> {
      friend class CMesh;
      friend class CMeshLoader;
      friend class sys::TSingleton<CMeshManager>;
    protected:
      CMeshManager();
      ~CMeshManager();
    public:
      static PMesh load(PMeshLoader pLoader);
  };

  class CGeometryManager : public cym::TResourceManager<CGeometry>, public sys::TSingleton<CGeometryManager> {
      friend class CGeometry;
      friend class CGeometryLoader;
      friend class sys::TSingleton<CGeometryManager>;
    public:
      using EFlag = CGeometry::EFlag;
    protected:
      std::map<sys::string,PGeometry> mGeometries;
    protected:
      CGeometryManager();
      ~CGeometryManager();
    public:
      inline static void boot() { CGeometryManager::getSingleton(); }
      /* remove geometry and return it */
      static PGeometry pull(const sys::string& tName) {
        SYS_LOG_NFO("cym::CGeometryManager::pull(sys::string&)");
        static auto& self {cym::CGeometryManager::getSingleton()};
        return self.mGeometries.extract(tName).mapped();
      }
      /* destroy geometry */
      static bool drop(const sys::string& tName) {
        SYS_LOG_NFO("cym::CGeometryManager::drop(sys::string&)");
        static auto& self {cym::CGeometryManager::getSingleton()};
        return self.mGeometries.size() < self.mGeometries.erase(tName);
      }
      /* find geometry */
      static PGeometry find(const std::string& tName) {
        SYS_LOG_NFO("cym::CGeometryManager::find(sys::string&)");
        static auto& self {cym::CGeometryManager::getSingleton()};
        PGeometry pGeometry;
        auto it = self.mGeometries.find(tName);
        if (it != self.mGeometries.end()) {
          pGeometry = it->second;
        }
        return {new CGeometry{*pGeometry}};
      }
      /* persist geometry */
      static void save(PGeometry pGeometry) {
        SYS_LOG_NFO("cym::CGeometryManager::save(PGeometry)");
        static auto& self {cym::CGeometryManager::getSingleton()};
        self.mGeometries.insert(std::pair(pGeometry->mName, pGeometry));
      }
      /* load PGeometry using a CGeometryLoader */
      static PGeometry load(PGeometryLoader pLoader, bool bSearch = true);
      /* load PGeometry using a TGeometryLoader */
      template<typename T> inline static PGeometry load(sys::ptr<TGeometryLoader<T>> pLoader, bool bSearch = true) { return CGeometryManager::load(CGeometryLoader{pLoader},bSearch); }
      /* load geometry routing to a geometry loader */
      template<typename T, typename... Args> static PGeometry load(const T& tSource, Args&&... args) {
        SYS_LOG_NFO("cym::CGeometryManager::load(T&,Args&&)");
        // manager
        static auto& self {CGeometryManager::getSingleton()};
        // temp geo for output
        PGeometry pGeometry;
        // gen name for seach
        const sys::string tName{CGeometryLoader::name(tSource,std::forward<Args>(args)...)};
        // try to find stored CGeometry and set it to (this local) pGeometry
        if (!sys::find(/*needle*/tName, /*haystack*/self.mGeometries, /*destination*/pGeometry)) {
          // put a custom loader into a generic loader (virtual load() methods will apply)
          PGeometryLoader tLoader{new TGeometryLoader<T>{tSource, std::forward<Args>(args)...}};
          // this will return an empty geometry imediatly, and async load its data (meshs,materials,textures,vbos)
          pGeometry = CGeometryManager::load(tLoader, false);
        }
        // return copy of CGeometry
        return {new CGeometry{*pGeometry}};
      }
  };
}

#endif //__cym_cgeometry_hpp__
