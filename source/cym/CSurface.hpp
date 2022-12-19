#ifndef __cym_csurface_hpp__
#define __cym_csurface_hpp__

#include "sys/sys.hpp"
#include "uix/CWindow.hpp"

namespace cym {
  class CSurface {
    public:
      CSurface() = default;
      virtual ~CSurface() = default;
  };

  class CConsoleSurface : public CSurface {
    protected:
      //CHAR_INFO* mBuffer {nullptr};
    public:
      CConsoleSurface() = default;
      ~CConsoleSurface() = default;
  };

  class CWindowSurface : public CSurface {

  };

  class CCanvasSurface : public CSurface {

  };
} // namespace cym


#endif //__cym_csurface_hpp__