#ifndef __ogl_cfile_hpp__
#define __ogl_cfile_hpp__

#include "sys/CFile.hpp"

namespace ogl {
  using CFile = sys::CFile;
  
  class CResourceFile : public CFile {
      using CFile::CFile;
  };
  
  class CTextureFile : public CResourceFile {
      using CResourceFile::CResourceFile;
  };
  
  class CDDSFile : public CTextureFile {
      
  };
  
  class CTGAFile : public CTextureFile {
      
  };
}

#endif //__ogl_cfile_hpp__
