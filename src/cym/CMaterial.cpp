#include "cym/CMaterial.hpp"

namespace cym {
  // channel /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CChannel::~CChannel() {
    SYS_LOG_NFO("cym::CChannel::~CChannel()::" << this);
  }
  
  // material ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CMaterial::CMaterial(const sys::string& tName/*=""*/) : cym::CResource(tName) { 
    SYS_LOG_NFO("cym::CMaterial::CMaterial(sys::string&)::" << this);
  }
  
  CMaterial::~CMaterial() {
    SYS_LOG_NFO("cym::CMaterial::~CMaterial()::" << this);
  }

  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CMaterialManager::CMaterialManager() { 
    SYS_LOG_NFO("cym::CMaterialManager::CMaterialManager()"); 
  }
  
  CMaterialManager::~CMaterialManager() { 
    SYS_LOG_NFO("cym::CMaterialManager::~CMaterialManager()"); 
    // mMaterials.clear(); 
  }
  
  PMaterial CMaterialManager::load(PMaterialLoader pLoader, bool bSearch/*=true*/) {
        SYS_LOG_NFO("cym::CMaterialManager::load(PMaterialLoader)");
        // manager
        static auto& self {cym::CMaterialManager::getSingleton()};
        
// @TODO implement bSearch
        
        // process material loader into a material
        if (pLoader) {
          PMaterial   pMaterial;
          const auto& tName {pLoader->getName()};
          // new material
          pMaterial = new CMaterial{tName};
          // save material
          CMaterialManager::save(pMaterial);
          // spawn task to thread
          sys::task([pMaterial, pLoader]() mutable {
            // load loader
            pLoader->load(pMaterial);
            // for each channel loader
            for (auto&& [eType, pChannelLoader] : pLoader->mChannelLoaders) {
              switch (eType) {
                case cym::EChannel::AMBIENT: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(PMaterialLoader)::AMBIENT");
          
                  auto pChannel {new TChannel<EChannel::AMBIENT>{}};
          
                  if (pChannelLoader->hasTextureLoader())
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->getTextureLoader());
          
                  pChannel->mColor = pChannelLoader->getColor();
          
                  pMaterial->addChannel(pChannel);
          
          
                  PGroup& pGroup = pMaterial->getGroup(EChannel::AMBIENT);
          
                  pGroup->setProperty("color", new TProperty<EProperty::COLOR>{pChannelLoader->getColor()});
          
          
                }
                break;
                case cym::EChannel::DIFFUSE: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(PMaterialLoader)::DIFFUSE");
          
                  auto pChannel = new TChannel<CChannel::EType::DIFFUSE>{};
          
                  if (pChannelLoader->hasTextureLoader()) {
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->getTextureLoader());
                  }
          
                  pChannel->mColor = pChannelLoader->getColor();
          
                  pMaterial->addChannel(pChannel);
                }
                break;
                case cym::EChannel::NORMAL: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(PMaterialLoader)::NORMAL");
          
                  auto pChannel = new TChannel<CChannel::EType::NORMAL>{};
          
                  if (pChannelLoader->hasTextureLoader())
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->getTextureLoader());;
          
                  pMaterial->addChannel(pChannel);
                }
                break;
                case cym::EChannel::SPECULAR: {
                  SYS_LOG_NFO("cym::CMaterialManager::load(PMaterialLoader)::SPECULAR");
          
                  auto pChannel = new TChannel<CChannel::EType::SPECULAR>{};
          
                  if (pChannelLoader->hasTextureLoader())
                    pChannel->mTexture = CTextureManager::load(pChannelLoader->getTextureLoader());;
          
                  pChannel->mColor = pChannelLoader->getColor();
          
                  pMaterial->addChannel(pChannel);
                }
                break;
                default:
                break;
              }
            }
            // update state
            pMaterial->mState = CResource::READY;
          }, sys::ETask::ASYNC);
          // return material
          return pMaterial;
        } else {
// @TODO return null material, inited on CMaterialManager::boot(), uses a simple null texture
          return nullptr;
        }
      }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
}
