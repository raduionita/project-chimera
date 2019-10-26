#include "glo/CEngine.hpp"

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
   
   void CEngine::free() {
     
   }
}
