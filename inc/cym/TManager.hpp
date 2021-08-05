#ifndef __cym_tmanager_hpp__
#define __cym_tmanager_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CManager {
      
  };
  
  template<typename T> class TManager : public CManager {
    public:
      typedef T managed_type;
  }; 
}

#endif //__cym_tmanager_hpp__
