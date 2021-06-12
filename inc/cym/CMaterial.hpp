#ifndef __cym_cmaterial_hpp__
#define __cym_cmaterial_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CTexture.hpp"
#include "cym/CProperty.hpp"
#include "cym/CInstance.hpp"

namespace cym {
  class CMateriaLoader;
  class CChannelLoader;
  class CMaterialManager;
  class CMaterial; class IMaterial;
  class CChannel; class IChannel;
  
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
      sys::sptr<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::AMBIENT; }
  };
  
  template<> class TChannel<CChannel::EType::DIFFUSE> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      cym::rgba          mColor;
      sys::sptr<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::DIFFUSE; }
  };
  
  template<> class TChannel<CChannel::EType::NORMAL> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::sptr<CTexture> mTexture;
    public:
      virtual inline EType getType() const override { return CChannel::EType::NORMAL; }
  };
  
  template<> class TChannel<CChannel::EType::SPECULAR> : public CChannel {
      friend class CMaterial;
      friend class CMaterialLoader;
      friend class CMaterialManager;
    protected:
      sys::sptr<CTexture> mTexture;
      cym::rgba          mColor;
      glm::real          mLevel;
    public:
      virtual inline EType getType() const override { return CChannel::EType::SPECULAR; }
  };
  
  class CMaterial : public cym::CResource {
      friend class IMaterial;
      friend class CChannel;
      friend class CMesh;
      friend class CModel;
      friend class CMaterialLoader;
      friend class CMaterialManager;
      using EChannel = cym::CChannel::EType;
    protected:
      sys::CMap<EChannel, sys::sptr<CChannel>> mChannels;
    public:
      using cym::CResource::CResource;
    public:
      CMaterial(const cym::name& tName = "") : cym::CResource(tName) { }
      ~CMaterial();
    public: // bind to shader?!, should trickle down to channel & texture
      template<typename T> bool bind(sys::sptr<T>) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); return false; }
    public:
      inline bool                isTransparent() const                        { return mChannels.find(EChannel::TRANSPARENCY) != mChannels.end(); }
      
      inline void                addChannel(sys::sptr<CChannel> pChannel)    { mChannels[pChannel->getType()] = pChannel; }
      template<EChannel T> inline void   addChannel(sys::sptr<TChannel<T>> pChannel) { mChannels[pChannel->getType()] = pChannel; }
      
      inline sys::sptr<CChannel>&                    getChannel(EChannel eChannel)                { return mChannels[eChannel]; }
      template<EChannel T> inline sys::sptr<TChannel<T>>     getChannel()  { return sys::static_pointer_cast<TChannel<T>>(mChannels[T]); }
      inline sys::sptr<TChannel<EChannel::AMBIENT>>  getAmbient()  { return sys::static_pointer_cast<TChannel<EChannel::AMBIENT>>(mChannels[EChannel::AMBIENT]); }
      inline sys::sptr<TChannel<EChannel::DIFFUSE>>  getDiffuse()  { return sys::static_pointer_cast<TChannel<EChannel::DIFFUSE>>(mChannels[EChannel::DIFFUSE]); }
      inline sys::sptr<TChannel<EChannel::NORMAL>>   getNormal()   { return sys::static_pointer_cast<TChannel<EChannel::NORMAL>>(mChannels[EChannel::NORMAL]); }
      inline sys::sptr<TChannel<EChannel::SPECULAR>> getSpecular() { return sys::static_pointer_cast<TChannel<EChannel::SPECULAR>>(mChannels[EChannel::SPECULAR]); }
  };
  
  // instances////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class IChannel : public cym::TInstance<CChannel> {
      using EField = cym::CChannel::EType;
    public:
      using cym::TInstance<CChannel>::TInstance;
    public:
      inline const CChannel& getChannel() const { return mInstance.raw(); }
  };
  
  class IMaterial : public cym::TInstance<CMaterial> {
      using EChannel = cym::CChannel::EType; 
    protected:
      sys::CMap<EChannel, sys::sptr<IChannel>> mChannels;
    public:
      using cym::TInstance<CMaterial>::TInstance;
    public:
      inline const CMaterial&    getMaterial() const { return mInstance.raw(); }
      inline sys::sptr<IChannel>& getChannel(EChannel eChannel) {
        auto& iChannel = mChannels[eChannel];
        if (!iChannel) {
          auto& pChannel = mInstance->getChannel(eChannel);
          if (pChannel) {
            iChannel = new IChannel{pChannel};
          }
        }
        return iChannel; 
      }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CChannelLoader : public CResourceLoader {
    protected:
      // fields
      sys::sptr<cym::CTextureLoader> mTextureLoader;
      cym::rgba                      mColor;
      glm::real                      mLevel {1.f};
    public:
      bool                            hasTextureLoader() { return mTextureLoader == true; }
      sys::sptr<cym::CTextureLoader>& useTextureLoader() { if (!mTextureLoader) mTextureLoader = new CTextureLoader; return mTextureLoader; }
      sys::sptr<cym::CTextureLoader>& getTextureLoader() { return mTextureLoader; }
      void                            setTextureLoader(sys::sptr<cym::CTextureLoader> pLoader) { mTextureLoader = pLoader; }
      
      cym::rgba&                     getColor() { return mColor; }
      glm::real&                     getLevel() { return mLevel; }
  };
  
  class CMaterialLoader : public CResourceLoader {
      friend class CMaterial;
      friend class CMaterialManager;
    public:
      enum EHint { BLINN = 1, PHONG = 2, LAMBERT = 4 };
    protected:
      std::map<cym::CChannel::EType,sys::sptr<cym::CChannelLoader>> mChannelLoaders;
      std::map<sys::string, sys::string>                                mUnknowns;
    public:// ctors
      using cym::CResourceLoader::CResourceLoader;
    public:
    public:
      virtual void load(sys::sptr<CResourceLoader>) {  };
    public:
      sys::sptr<cym::CChannelLoader>&                                getChannelLoader(cym::CChannel::EType eType) { auto& pLoader = mChannelLoaders[eType]; if (!pLoader) pLoader = new CChannelLoader; return pLoader; }
      sys::map<cym::CChannel::EType,sys::sptr<cym::CChannelLoader>>& getChannelLoaders()                          { return mChannelLoaders; }
      void                                                               addUnknown(const std::string& key, const std::string& val) { mUnknowns[key] = val; }
  };
  
  template<typename T> class TMaterialLoader : public CMaterialLoader { };
  
  template<> class TMaterialLoader<sys::CFile> : public CMaterialLoader {
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
  
  class CMaterialManager : public cym::CManager, public sys::TSingleton<CMaterialManager> {
      friend class CMaterial;
      friend class CMaterialLoader;
    protected:
      sys::CMap<std::string, sys::sptr<CMaterial>> mMaterials;
    public:
      CMaterialManager();
      ~CMaterialManager();
    public:
      static void save(sys::sptr<CMaterial> pMaterial) {
        static auto pThis {CMaterialManager::getSingleton()};
        CYM_LOG_NFO("cym::CMaterialManager::save(sys::sptr<CMaterial>)::" << pThis);
        pThis->mMaterials.insert(std::pair(pMaterial->mName, pMaterial));
      }
      
      static sys::sptr<CMaterial> load(sys::sptr<CMaterialLoader> pMaterialLoader) {
        static auto pThis {cym::CMaterialManager::getSingleton()};
        CYM_LOG_NFO("cym::CMaterialManager::load(sys::sptr<CMaterialLoader>)::" << pThis);
        
        if (!pMaterialLoader) return nullptr;
        
        sys::sptr<CMaterial> pMaterial = new CMaterial{pMaterialLoader->getName()};
        
        sys::async([pMaterial, pMaterialLoader](){
          
          pMaterialLoader->load(pMaterialLoader);
          
          for (auto&& [eType, pChannelLoader] : pMaterialLoader->mChannelLoaders) {
            switch (eType) {
              case CChannel::EType::AMBIENT: {
                CYM_LOG_NFO("cym::CMaterialManager::load(...)::AMBIENT");
                
                auto  pChannel = new TChannel<CChannel::EType::AMBIENT>{};
                
                if (pChannelLoader->hasTextureLoader())
                  pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());
                
                pChannel->mColor   = pChannelLoader->getColor();
                
                pMaterial->addChannel(pChannel);
              } break;
              case CChannel::EType::DIFFUSE: {
                CYM_LOG_NFO("cym::CMaterialManager::load(...)::DIFFUSE");
                
                auto  pChannel = new TChannel<CChannel::EType::DIFFUSE>{};
                
                if (pChannelLoader->hasTextureLoader())
                  pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());
                  
                pChannel->mColor   = pChannelLoader->getColor();
                
                pMaterial->addChannel(pChannel);
              } break;
              case CChannel::EType::NORMAL: {
                CYM_LOG_NFO("cym::CMaterialManager::load(...)::NORMAL");
                
                auto  pChannel = new TChannel<CChannel::EType::NORMAL>{};
                
                if (pChannelLoader->hasTextureLoader())
                  pChannel->mTexture = CTextureManager::load(pChannelLoader->useTextureLoader());;
                
                pMaterial->addChannel(pChannel);
              } break;
              case CChannel::EType::SPECULAR: {
                CYM_LOG_NFO("cym::CMaterialManager::load(...)::SPECULAR");
                
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
        
        CMaterialManager::save(pMaterial);
        
        return pMaterial;
      }
  };
  
  // class CStandartMaterial
  // class CMultipleMaterial
}

#endif //__cym_cmaterial_hpp__
