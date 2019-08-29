#ifndef __cym_uix_cframe_hpp__
#define __cym_uix_cframe_hpp__

#include "uix.hpp"
#include "CToplevel.hpp"

namespace cym { namespace uix {
  class CFrame : public CToplevel {
    using CToplevel::CToplevel;
    typedef CToplevel super;
    public:
      CFrame() = default;
      CFrame(                                                                int);
      CFrame(CWindow*, const SString& = "", const SShape& = SShape::DEFAULT, int = 0);
      ~CFrame();
    protected:
      virtual bool init(CWindow*, const SShape&, int) override;
              bool init(CWindow*, const SString&, const SShape&, int);
  };
}}

#endif //__cym_uix_cframe_hpp__
