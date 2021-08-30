#ifndef __cym_cmaterial_hpp__
#define __cym_cmaterial_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CTexture.hpp"
#include "cym/TProperty.hpp"
#include "cym/TInstance.hpp"


// @TODO class CMaterial
// @TODO class CTexture extends CMaterial
// @TODO class CSurface extends CMaterial // surface has all properties that CMaterial has now

// OR

// @TODO class CMaterial
//       sys::table<sys::string, PProperty> mProperties; // a list of properties
//       each property knows how to bind to the shader

// @TODO class TProperty<CTexture>  extends CProperty
// @TODO class TProperty<CMaterial> extends CProperty
// @TODO class TProperty<CGroup>    extends CProperty
//       sys::table<sys::string,PProperty> mProperties // texture (or other material) + value/level


namespace cym {
  class CMaterialLoader;  typedef sys::ptr<CMaterialLoader> PMaterialLoader;
  class CChannelLoader;   typedef sys::ptr<CChannelLoader>  PChannelLoader;
  class CMaterialManager;
  class CMaterial;        typedef sys::ptr<CMaterial>       PMaterial;
  class CChannel;         typedef sys::ptr<CChannel>        PChannel;
  
  enum class EChannel : uint { NONE = 0, DIFFUSE = 1, AMBIENT, NORMAL, SPECULAR, EMISSION, TRANSPARENCY, REFRCTION };
  
  class CGroup; typedef sys::ptr<CGroup> PGroup;
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @TODO use CProperty
// CChannel = wrapper around map of properties

// @TODO replace CChannel w/ CGroup
  class CGroup {
    protected:
      
// @TODO reaplce w/ sys::vector<sys::pair<EProperty,PProperty>>
      sys::map<sys::string, PProperty> mProperties;

    public:
      PProperty& getProperty(const sys::string& tName) { return sys::find_or_throw(tName, mProperties, sys::exception("Property"+ tName +" NOT found!",__FILE__,__LINE__)); }
      template<EProperty E> void setProperty(const sys::string& tName, TProperty<E>* pProperty) { mProperties.insert(std::pair{tName, pProperty}); }
      template<EProperty E> void setProperty(const sys::string& tName, sys::ptr<TProperty<E>> pProperty) { mProperties.insert(std::pair{tName, pProperty}); }
  };

  
  
  class CChannel : cym::CResource {
    public:
      using EType = EChannel;
    public:
      ~CChannel();
    public:
      virtual inline EType getType() const { throw sys::exception("CChannel::getType() NOT overridden!",__FILE__,__LINE__); }  
  };
  
  template<CChannel::EType T> class TChannel : public CChannel { };
  
  template<> class TChannel<CChannel::EType::AMBIENT> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      cym::rgba          mColor;
      sys::ptr<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::AMBIENT; }
  };
  
  template<> class TChannel<CChannel::EType::DIFFUSE> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      cym::rgba          mColor;
      sys::ptr<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::DIFFUSE; }
  };
  
  template<> class TChannel<CChannel::EType::NORMAL> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::ptr<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::NORMAL; }
  };
  
  template<> class TChannel<CChannel::EType::SPECULAR> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::ptr<CTexture> mTexture;
      cym::rgba          mColor;
      glm::real          mLevel;
    public:
      virtual inline EType getType() const override { return CChannel::EType::SPECULAR; }
  };
  
  class CMaterial : public cym::CResource {
      friend class CChannel;
      friend class CMesh;
      friend class CGeometry;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::map<EChannel,PChannel> mChannels;
      
// @TODO reaplce w/ sys::vector<sys::pair<EChannel,PChannel>>
      sys::map<EChannel, PGroup> mGroups;
      
      
      
    public:
      using cym::CResource::CResource;
      CMaterial(const sys::string& = "");
      ~CMaterial();
    public:
      inline bool                isTransparent() const                      { return mChannels.find(EChannel::TRANSPARENCY) != mChannels.end(); }
      /* */
      inline void                addChannel(sys::ptr<CChannel> pChannel)    { mChannels[pChannel->getType()] = pChannel; }
      template<EChannel T> inline void   addChannel(sys::ptr<TChannel<T>> pChannel) { mChannels[pChannel->getType()] = pChannel; }
      /* */
      inline sys::ptr<CChannel>&                    getChannel(EChannel eChannel)                { return mChannels[eChannel]; }
      template<EChannel T> inline sys::ptr<TChannel<T>>     getChannel()  { return sys::static_pointer_cast<TChannel<T>>(mChannels[T]); }
      inline sys::ptr<TChannel<EChannel::AMBIENT>>  getAmbient()  { return sys::static_pointer_cast<TChannel<EChannel::AMBIENT>>(mChannels[EChannel::AMBIENT]); }
      inline sys::ptr<TChannel<EChannel::DIFFUSE>>  getDiffuse()  { return sys::static_pointer_cast<TChannel<EChannel::DIFFUSE>>(mChannels[EChannel::DIFFUSE]); }
      inline sys::ptr<TChannel<EChannel::NORMAL>>   getNormal()   { return sys::static_pointer_cast<TChannel<EChannel::NORMAL>>(mChannels[EChannel::NORMAL]); }
      inline sys::ptr<TChannel<EChannel::SPECULAR>> getSpecular() { return sys::static_pointer_cast<TChannel<EChannel::SPECULAR>>(mChannels[EChannel::SPECULAR]); }
      
      
      inline PGroup& operator [](EChannel e) { return getGroup(e); }
      inline PGroup& getGroup(EChannel e)                 { auto it {mGroups.find(e)}; if (it == mGroups.end()) { mGroups.insert(std::pair{e,new CGroup{}}); } return mGroups[e]; }
      inline void    setGroup(EChannel e, PGroup& pGroup) { mGroups[e] = pGroup; }
      
    public: // actions
      /* bind to shader?!, should trickle down to channel & texture */
      template<typename T> bool bind(sys::ptr<T>) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); return false; }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CChannelLoader : public CResourceLoader {
    protected:
      // fields
      PTextureLoader mTextureLoader;
      cym::rgba      mColor;
      glm::real      mLevel {1.f};
    public:
      bool           hasTextureLoader() { return mTextureLoader != nullptr; }
      PTextureLoader getTextureLoader() { return mTextureLoader; }
      void           setTextureLoader(PTextureLoader pLoader) { mTextureLoader = pLoader; }
      PTextureLoader useTextureLoader() { if (!mTextureLoader) { mTextureLoader = new CTextureLoader; } return mTextureLoader; }
      
      cym::rgba&      getColor() { return mColor; }
      void            setColor(const cym::rgba& c) { mColor = c; }
      glm::real&      getLevel() { return mLevel; }
      void            setLevel(const glm::real l) { mLevel = l; }
  };
  
  class CMaterialLoader : public CResourceLoader {
      friend class CMaterial;
      friend class CMaterialManager;
    public:
      enum EHint { BLINN = 1, PHONG = 2, LAMBERT = 4 };
    protected:
      std::map<EChannel,PChannelLoader> mChannelLoaders;
      std::map<sys::string,sys::string> mUnknowns;
    public:// ctors
      using cym::CResourceLoader::CResourceLoader;
    public:
    public:
      inline virtual void load(PMaterial) { SYS_LOG_NFO("cym::CMaterialLoader::load(PMaterial)::" << this); }
    public:
      PChannelLoader&                    getChannelLoader(cym::CChannel::EType eType) { auto& pLoader = mChannelLoaders[eType]; if (!pLoader) pLoader = new CChannelLoader; return pLoader; }
      sys::map<EChannel,PChannelLoader>& getChannelLoaders()                          { return mChannelLoaders; }
      void                               addUnknown(const std::string& key, const std::string& val) { mUnknowns[key] = val; }
  };
  
  template<typename T> class TMaterialLoader : public CMaterialLoader { };
  
  template<> class TMaterialLoader<sys::file> : public CMaterialLoader {
      friend class CMaterial;
      friend class CMaterialManager;
    protected:
      sys::file mFile;
    public:
      TMaterialLoader(const sys::file& tFile) : mFile{tFile} { };
    public:
      inline static std::string name(const sys::file& tFile) { return tFile.path(); }
    public:
      sys::file& getFile() { return mFile; }
  };
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMaterialManager : public cym::TResourceManager<CMaterial>, public sys::TSingleton<CMaterialManager> {
      friend class cym::CMaterial;
      friend class cym::CMaterialLoader;
      friend class sys::TSingleton<cym::CMaterialManager>;
    protected:
      sys::CMap<std::string,cym::PMaterial> mMaterials;
    protected:
      CMaterialManager();
      ~CMaterialManager();
    public:
      inline static void boot() { CMaterialManager::getSingleton(); }
      /* remember CMaterial inside CMaterialManager */
      static void save(PMaterial pMaterial) {
        static auto& self {CMaterialManager::getSingleton()};
        SYS_LOG_NFO("cym::CMaterialManager::save(PMaterial)");
        self.mMaterials.insert(std::pair(pMaterial->mName, pMaterial));
      }
      /* load CMaterial using a CMaterialLoader */
      static PMaterial load(PMaterialLoader pLoader, bool bSearch=true);
  };
  
// @todo
  // class CBaseMaterial
  // class CMultiMaterial
  // class CNullMaterial
}

#endif //__cym_cmaterial_hpp__
