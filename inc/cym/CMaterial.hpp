#ifndef __cym_cmaterial_hpp__
#define __cym_cmaterial_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CTexture.hpp"
#include "cym/CProperty.hpp"
#include "cym/TInstance.hpp"

namespace cym {
  class CMateriaLoader;
  class CChannelLoader;
  class CMaterialManager;
  class CMaterial;
  class CChannel;
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CChannel : cym::CResource {
    public:
      enum EType  : uint { NONE = 0, DIFFUSE = 1, AMBIENT, NORMAL, SPECULAR, EMISSION, TRANSPARENCY, REFRCTION };
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
      sys::spo<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::AMBIENT; }
  };
  
  template<> class TChannel<CChannel::EType::DIFFUSE> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      cym::rgba          mColor;
      sys::spo<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::DIFFUSE; }
  };
  
  template<> class TChannel<CChannel::EType::NORMAL> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::spo<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::NORMAL; }
  };
  
  template<> class TChannel<CChannel::EType::SPECULAR> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::spo<CTexture> mTexture;
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
      using EChannel = cym::CChannel::EType;
    protected:
      sys::CMap<EChannel,sys::spo<CChannel>> mChannels;
    public:
      using cym::CResource::CResource;
      CMaterial(const sys::string& tName = "") : cym::CResource(tName) { }
      ~CMaterial();
    public: // bind to shader?!, should trickle down to channel & texture
      template<typename T> bool bind(sys::spo<T>) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); return false; }
    public:
      inline bool                isTransparent() const                        { return mChannels.find(EChannel::TRANSPARENCY) != mChannels.end(); }
      
      inline void                addChannel(sys::spo<CChannel> pChannel)    { mChannels[pChannel->getType()] = pChannel; }
      template<EChannel T> inline void   addChannel(sys::spo<TChannel<T>> pChannel) { mChannels[pChannel->getType()] = pChannel; }
      
      inline sys::spo<CChannel>&                    getChannel(EChannel eChannel)                { return mChannels[eChannel]; }
      template<EChannel T> inline sys::spo<TChannel<T>>     getChannel()  { return sys::static_pointer_cast<TChannel<T>>(mChannels[T]); }
      inline sys::spo<TChannel<EChannel::AMBIENT>>  getAmbient()  { return sys::static_pointer_cast<TChannel<EChannel::AMBIENT>>(mChannels[EChannel::AMBIENT]); }
      inline sys::spo<TChannel<EChannel::DIFFUSE>>  getDiffuse()  { return sys::static_pointer_cast<TChannel<EChannel::DIFFUSE>>(mChannels[EChannel::DIFFUSE]); }
      inline sys::spo<TChannel<EChannel::NORMAL>>   getNormal()   { return sys::static_pointer_cast<TChannel<EChannel::NORMAL>>(mChannels[EChannel::NORMAL]); }
      inline sys::spo<TChannel<EChannel::SPECULAR>> getSpecular() { return sys::static_pointer_cast<TChannel<EChannel::SPECULAR>>(mChannels[EChannel::SPECULAR]); }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CChannelLoader : public CResourceLoader {
    protected:
      // fields
      sys::spo<cym::CTextureLoader> mTextureLoader;
      cym::rgba                      mColor;
      glm::real                      mLevel {1.f};
    public:
      bool                           hasTextureLoader() { return mTextureLoader == true; }
      sys::spo<cym::CTextureLoader>& useTextureLoader() { if (!mTextureLoader) mTextureLoader = new CTextureLoader; return mTextureLoader; }
      sys::spo<cym::CTextureLoader>& getTextureLoader() { return mTextureLoader; }
      void                           setTextureLoader(sys::spo<cym::CTextureLoader> pLoader) { mTextureLoader = pLoader; }
      
      cym::rgba&                     getColor() { return mColor; }
      void                           setColor(const cym::rgba& c) { mColor = c; }
      glm::real&                     getLevel() { return mLevel; }
      void                           setLevel(const glm::real l) { mLevel = l; }
  };
  
  class CMaterialLoader : public CResourceLoader {
      friend class CMaterial;
      friend class CMaterialManager;
    public:
      enum EHint { BLINN = 1, PHONG = 2, LAMBERT = 4 };
    protected:
      std::map<cym::CChannel::EType,sys::spo<cym::CChannelLoader>> mChannelLoaders;
      std::map<sys::string, sys::string>                           mUnknowns;
    public:// ctors
      using cym::CResourceLoader::CResourceLoader;
    public:
    public:
      virtual void load(sys::spo<CResourceLoader>) {  };
    public:
      sys::spo<cym::CChannelLoader>&                                getChannelLoader(cym::CChannel::EType eType) { auto& pLoader = mChannelLoaders[eType]; if (!pLoader) pLoader = new CChannelLoader; return pLoader; }
      sys::map<cym::CChannel::EType,sys::spo<cym::CChannelLoader>>& getChannelLoaders()                          { return mChannelLoaders; }
      void                                                               addUnknown(const std::string& key, const std::string& val) { mUnknowns[key] = val; }
  };
  
  template<typename T> class TMaterialLoader : public CMaterialLoader { };
  
  template<> class TMaterialLoader<sys::file> : public CMaterialLoader {
      friend class CMaterial;
      friend class CMaterialManager;
    protected:
      sys::CFile mFile;
    public:
      TMaterialLoader(const sys::CFile& tFile) : mFile{tFile} { };
    public:
      inline static std::string name(const sys::CFile& tFile) { return tFile.path(); }
    public:
      sys::CFile& getFile() { return mFile; }
  };
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMaterialManager : public cym::TResourceManager<CMaterial>, public sys::TSingleton<CMaterialManager> {
      friend class CMaterial;
      friend class CMaterialLoader;
    protected:
      sys::CMap<std::string, sys::spo<CMaterial>> mMaterials;
    public:
      CMaterialManager();
      ~CMaterialManager();
    public:
      /* remember CMaterial inside CMaterialManager */
      static void save(sys::spo<CMaterial> pMaterial) {
        static auto pThis {CMaterialManager::getSingleton()};
        SYS_LOG_NFO("cym::CMaterialManager::save(sys::spo<CMaterial>)::" << pThis);
        pThis->mMaterials.insert(std::pair(pMaterial->mName, pMaterial));
      }
      /* load CMaterial using a CMaterialLoader */
      static sys::spo<CMaterial> load(sys::spo<CMaterialLoader> pMaterialLoader, bool bExternal = true) {
        static auto pThis {cym::CMaterialManager::getSingleton()};
        SYS_LOG_NFO("cym::CMaterialManager::load(sys::spo<CMaterialLoader>)::" << pThis);
        // process material loader into a material
        if (pMaterialLoader) {
          sys::spo<CMaterial> pMaterial = new CMaterial{pMaterialLoader->getName()};
          // spawn task to thread
          sys::async([pMaterial, pMaterialLoader](){
            // load loader
            pMaterialLoader->load(pMaterialLoader);
            // for each channel loader
            for (auto&& [eType, pChannelLoader] : pMaterialLoader->mChannelLoaders) {
              switch (eType) {
                case CChannel::EType::AMBIENT: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(...)::AMBIENT");
                  
                  auto  pChannel = new TChannel<CChannel::EType::AMBIENT>{};
                  
                  if (pChannelLoader->hasTextureLoader())
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());
                  
                  pChannel->mColor   = pChannelLoader->getColor();
                  
                  pMaterial->addChannel(pChannel);
                } break;
                case CChannel::EType::DIFFUSE: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(...)::DIFFUSE");
                  
                  auto pChannel = new TChannel<CChannel::EType::DIFFUSE>{};
                  
                  if (pChannelLoader->hasTextureLoader()) {
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());
                  }
                    
                  pChannel->mColor   = pChannelLoader->getColor();
                  
                  pMaterial->addChannel(pChannel);
                } break;
                case CChannel::EType::NORMAL: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(...)::NORMAL");
                  
                  auto  pChannel = new TChannel<CChannel::EType::NORMAL>{};
                  
                  if (pChannelLoader->hasTextureLoader())
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());;
                  
                  pMaterial->addChannel(pChannel);
                } break;
                case CChannel::EType::SPECULAR: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(...)::SPECULAR");
                  
                  auto  pChannel = new TChannel<CChannel::EType::SPECULAR>{};
                  
                  if (pChannelLoader->hasTextureLoader())
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());;
                    
                  pChannel->mColor   = pChannelLoader->getColor();
                  
                  pMaterial->addChannel(pChannel);
                } break;
                default: break;
              }
            }
          }, sys::EAsync::SPAWN);
          // save material
          CMaterialManager::save(pMaterial);
          // return material
          return pMaterial;
        } else {
// @todo: return null material
          return nullptr;
        }
      }
  };
  
// @todo
  // class CBaseMaterial
  // class CMultiMaterial
  // class CNullMaterial
}

#endif //__cym_cmaterial_hpp__
