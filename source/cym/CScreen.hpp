#ifndef __cym_cscreen_hpp__
#define __cym_cscreen_hpp__

#include "cym/cym.hpp"
#include "sys/TSingleton.hpp"
#include "sys/CLogger.hpp"
#include "uix/CWindow.hpp"

#include <list>
#include <vector>

namespace cym {
  class CScreenManager : public sys::TSingleton<CScreenManager> {
      friend class sys::TSingleton<CScreenManager>;
      friend class cym::CScreen;
    private:
      std::vector<CScreen*> mScreens;
    private:
      CScreenManager();
    public:
      ~CScreenManager();
    public:
      static bool bootup();
      static void insert(cym::CScreen* pScreen);
      static void remove(cym::CScreen* pScreen);
      static bool update(float fElapsed=0.f);
  };

  class CScreen {
      friend class CScreenManager;
    protected:
      uix::CWindow*&          mParent;
    private:
      cym::CSurface*          mSurface {nullptr};
      std::list<cym::CLayer*> mLayers;
    public:
      // ctor
      template<typename T> CScreen(T*& pParent) : mParent{pParent} { 
        LOGDBG("cym::CScreen::CScreen(T*&)");
        CScreenManager::insert(this);
      }
      // dtor
      ~CScreen();
    public:
      bool update(float fElapsed=0.f);
  };
} // namespace cym


#endif //__cym_cscreen_hpp__