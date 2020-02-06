#include "ogl/CCore.hpp"

namespace ogl {
  CCore::CCore() {
    log::nfo << "ogl::CCore::CCore()::" << this << log::end;
    init();
  }
  
  CCore::~CCore() {
    log::nfo << "ogl::CCore::CCore::" << this << log::end;
    free();
  }
  
  void CCore::init() {
    load(new ogl::CTextureManager);
  }
  
  void CCore::free() {
    
  }
}
