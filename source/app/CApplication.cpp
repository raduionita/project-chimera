#include "app/CApplication.hpp"

namespace app {
  void CApplication::onInit() {
    LOGDBG("app::CApplication::onInit()");

    // cym::PContext pContext {getContext()};
    // cym::PScreen pScreen {new CScreen};
    // pScreen->addLayer("main", pLayer);
    // pContext->addScreen("game", pScreen);

    cym::PScreen pScreen {new cym::CScreen};
    cym::PController pGameControler {new cym::CController};
    cym::PLayer pGameLayer {new cym::CLayer};
    pScreen->setLayer(); // info/gui
    pScreen->setLayer(); // game
  }

  void CApplication::onTick(float fDelta) {
    LOGDBG("app::CApplication::onTick("<< fDelta <<")");
    quit(0);
  }
} // namespace app
