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
     load<ogl::CTextureManager>();
   } 
   
   void CEngine::free() {
     
   }
   
   // @usage: load<ogl::CTextureManager>();
   template <> ogl::CTextureManager* CEngine::load<ogl::CTextureManager>() {
     // loads default or through extending ogl::CEngine, replace logic
     throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__);
   }
   
   // @usage: load(new ogl::CTextureManager);
   template <> ogl::CTextureManager* CEngine::load<ogl::CTextureManager>(ogl::CTextureManager*) {
     // dynamic replacement, w/o needing to extend ogl::CEngine 
     throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__);
   }
}
