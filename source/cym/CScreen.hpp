#ifndef __cym_cscreen_hpp__
#define __cym_cscreen_hpp__

#include "cym/cym.hpp"
#include "cym/TManager.hpp"

#include <vector>
#include <utility>
#include <string>

namespace cym {
  using PLayer  = sys::ptr<CLayer>;
  using PScreen = sys::ptr<CScreen>;


  class CLayer {
    public:
      CLayer() = default;
      virtual ~CLayer() = default;
  };

  class CScreen {
    private:
      std::vector<std::pair<std::string, cym::PLayer>> mLayers;
    public:
      CScreen() = default;
      virtual ~CScreen() = default;
    public:
      void setLayer(const std::string& name, cym::PLayer pLayer) {

      }
      
      const cym::PLayer& getLayer(const std::string& name) {
        for (const auto& tLayer : mLayers) {
          if (tLayer.first == name) {
            return tLayer.second;
          }
        }
        // throw error
      }
  };

  class CScreenManager : public cym::TManager<CScreen>, public sys::TSingleton<CScreenManager> {
    public:
      static bool bootup() {
        // bootup all screens
        return true;
      }
  };
} // namespace cym

#endif //__cym_cscreen_hpp__