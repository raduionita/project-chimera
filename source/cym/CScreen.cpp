#include "cym/CScreen.hpp"
#include "cym/CLayer.hpp"

namespace cym {
  CScreen::CScreen() {

  }

  CScreen::~CScreen() {
    for (auto pLayer : mLayers) {
      delete pLayer;
    }
    mLayers.clear();
  }
} // namespace cym
