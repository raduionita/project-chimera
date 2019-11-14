#include "ogl/CEngine.hpp"

namespace ogl {
  CEngine::CEngine() {
    log::nfo << "ogl::CEngine::CEngine()::" << this << log::end;
    init();
  }
  
  CEngine::~CEngine() {
    log::nfo << "ogl::CEngine::~CEngine()::" << this << log::end;
    free();
  }
  
  void CEngine::init() {
    load(new ogl::CTextureManager);
  }
  
  void CEngine::free() {
    
  }
}
