#ifndef __glo_hpp__
#define __glo_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"
#include "glc/glc.hpp"

#undef FAR
#undef NEAR

namespace glo {
  class CShader;
  class CObject;
    class CBuffer;
      class CVertexBuffer;
      class CIndexBuffer;
    class CLayout;
      class CVertexLayout;
    class CArray;
      class CVertexArray;
    class CProgram;
    class CUniform;
  class CVertex; // @todo: this should be a template that describes components
  class CVertexLayout;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  using log = sys::log;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}



#endif //__glo_hpp__
