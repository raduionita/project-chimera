#include "cym/CScreen.hpp"
#include "cym/CLayer.hpp"
#include "sys/CException.hpp"
#include "cym/CSurface.hpp"

#include <algorithm>

namespace cym {
  // screen manager //////////////////////////////////////////////////////////////////////////////////////////////////
  
  CScreenManager::CScreenManager() {
    LOGDBG("cym::CScreenManager::CScreenManager()");
  }

  CScreenManager::~CScreenManager() {
    LOGDBG("cym::CScreenManager::~CScreenManager()");
    for (CScreen* pScreen : mScreens) {
      delete pScreen;
      pScreen = nullptr;
    }
    mScreens.clear();
  }

  bool CScreenManager::bootup() {
    LOGDBG("cym::CScreenManager::bootup()");
    static auto& self {CScreenManager::getSingleton()};
    for (auto& pScreen : self.mScreens) {
      sys::throw_if(pScreen->mSurface != nullptr, "CScreen must have a CSurface");
      if (pScreen->mLayers.empty()) {
        pScreen->mLayers.push_front(new cym::CLayer{pScreen->mSurface});
      }
    }
    return true;
  }

  void CScreenManager::insert(CScreen* pScreen) {
    static auto& self {CScreenManager::getSingleton()};
    self.mScreens.push_back(pScreen);
  }

  void CScreenManager::remove(CScreen* pScreen) {
    static auto& self {CScreenManager::getSingleton()};
    self.mScreens.erase(std::remove(self.mScreens.begin(), self.mScreens.end(), pScreen), self.mScreens.end()); 
  }

  bool CScreenManager::update(float fElapsed/*=0.f*/) {
    static auto& self {CScreenManager::getSingleton()};
    for (CScreen* pScreen : self.mScreens) {
      pScreen->update(fElapsed);
    }
    return true;
  }
  
  // screen //////////////////////////////////////////////////////////////////////////////////////////////////////////

  CScreen::~CScreen() {
    LOGDBG("cym::CScreen::~CScreen()");
    // layers
    for (CLayer*& pLayer : mLayers) {
      delete pLayer; pLayer = nullptr;
    }
    mLayers.clear();
    // surface
    delete mSurface; mSurface = nullptr;
  }

  bool CScreen::update(float fElapsed/*=0.f*/) {
    for (CLayer* pLayer : mLayers) {

    }

    // todo: present = merge layers into 1 surface

    return true;
  }
} // namespace cym
