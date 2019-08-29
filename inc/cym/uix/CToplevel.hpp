#ifndef __cym_uix_ctoplevel_hpp__
#define __cym_uix_ctoplevel_hpp__

#include "uix.hpp"
#include "CWindow.hpp"

namespace cym { namespace uix { 
  class CToplevel : public CWindow {
    using CWindow::CWindow;
    typedef CWindow super;
    public:
      CToplevel() = default;
      ~CToplevel();
  };
}}

#endif //__cym_uix_ctoplevel_hpp__
