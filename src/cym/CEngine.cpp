#include "cym/CEngine.hpp"

namespace cym {
   CEngine::CEngine() {
     log::nfo << "cym::CEngine::CEngine()::" << this << log::end;
     init();
   }
   
   CEngine::~CEngine() {
     log::nfo << "cym::CEngine::~CEngine()::" << this << log::end;
     free();
   }
   
   void CEngine::init() {
     
   } 
   
   void CEngine::loop() {
     
   }
   
   void CEngine::free() {
     
   }
}
