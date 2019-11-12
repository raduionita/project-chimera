#ifndef __ogl_ctextureloader_hpp__
#define __ogl_ctextureloader_hpp__

#include "ogl/CResource.hpp"
#include "sys/CException.hpp"

namespace ogl {
  class CTextureLoader; typedef sys::CPointer<CTextureLoader> PTextureLoader;
  class CTextureStream; typedef sys::CPointer<CTextureStream> PTextureStream;
  
  class CTextureStream : public CResourceStream {
    protected:
      // meta
      uint   mWidth;
      uint   mHeight;
      uint   mDepth;
      size_t mSize;
      uint   mMipmaps;
      uint   mFlags;
      uint   mFormat;
      // data
      ubyte* mStart;
      ubyte* mCursor;
      ubyte* mLast;
  };
  
  class CTextureLoader : public CResourceLoader {
      using ogl::CResourceLoader::CResourceLoader;
    public:
      virtual PTextureStream load(const sys::CString& file) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
  };
  
  class CDDSTextureLoader : public CTextureLoader {
      using ogl::CTextureLoader::CTextureLoader;
    public:
      virtual inline bool able(const sys::CString& file) const { return 0 == file.substr(file.find_first_of(".")+1).compare("dds"); }
      virtual PTextureStream load(const sys::CString& file);
  };
  
  class CTGATextureLoader : public CTextureLoader {
      using ogl::CTextureLoader::CTextureLoader;
    public:
      virtual inline bool able(const sys::CString& file) const { return 0 == file.substr(file.find_first_of(".")+1).compare("tga"); }
      virtual PTextureStream load(const sys::CString& file) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
  };
}

#endif //__ogl_ctextureloader_hpp__
