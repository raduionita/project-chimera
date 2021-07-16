#ifndef __sys_clayered_hpp__
#define __sys_clayered_hpp__

#include "sys/sys.hpp"

#include <list>

namespace sys {
  class CLayer {
      
  };
  
  class CLayered {
    protected:
      std::list<CLayer*> mLayers;
    public:
      CLayered() {
        
      }
      
      virtual ~CLayered() { }
  
    public:
      void front(CLayer*);
      void back(CLayer*);
      CLayer* pull();
  };
  
// @todo: separete what get's rendered:
  // stats (fps)
  // gui (on window menus)
  // tools (gizmo, )
  // scene
  // background (2d games)
}

#endif //__sys_clayered_hpp__
