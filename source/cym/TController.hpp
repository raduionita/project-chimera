#ifndef __cym_tcontroller_hpp__
#define __cym_tcontroller_hpp__

#include "cym/cym.hpp"
#include "cym/TManager.hpp"
#include "sys/CLogger.hpp"
#include "cym/CModifier.hpp"

#include <vector>
#include <map>
#include <string>

namespace cym {  
  using PProcess    = sys::ptr<CProcess>;
  using PController = sys::ptr<CController>;

  
  class CProcess {
    private:
      std::vector<PModifier> mModifiers;
    public:
      void onTick(float fDelta) {
        for (auto& pModifier : mModifiers) {
          pModifier->onTick(fDelta);
        }
      }
  };

  
  class CController {
    friend class CControllerManager;
    public:
      CController() { }
      virtual ~CController() { }
    public:
      virtual void onTick(float fDelta) { }
  };

  template <typename T> class TController : public CController {
    private:
      std::map<std::string, PProcess> mProcesses;
      T*                              mTarget;    // TNode<CModel>
    public:
      virtual bool onTick(float fDelta) {
        for (auto& [id, pProcess] : mProcesses) {
          pProcess->onTick(fDelta);
        }
      }
  };


  class CControllerManager : public TManager<CController>, public sys::TSingleton<CControllerManager> {
      friend class CController;
    private:
      std::vector<PController> mControllers;
    private:
      static void insert(CController* pController) {
        static auto& self {cym::CControllerManager::getSingleton()};
        self.mControllers.push_back(std::move(PController{pController}));
      }
    public:
      static bool bootup() {
        LOGDBG("cym::CControllerManager::bootup()");
        cym::CControllerManager::getSingleton();
        return true;
      }

      static bool update(float fDelta) {
        LOGDBG("cym::CControllerManager::onTick(fDelta)");
        static auto& self {cym::CControllerManager::getSingleton()};

        for (auto& pController : self.mControllers) {
          pController->onTick(fDelta);
        }

        return true;
      }
  };
} // namespace cym

#endif //__cym_tcontroller_hpp__