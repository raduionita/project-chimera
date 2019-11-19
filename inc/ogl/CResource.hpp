#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"
#include "sys/CException.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>
#include <functional>
#include <any>

namespace ogl {
  class CResource;        typedef sys::CPointer<CResource>        PResource;
  class CResourceManager; typedef sys::CPointer<CResourceManager> PResourceManager;
  class CResourceStream;  typedef sys::CPointer<CResourceStream>  PResourceStream;
  class CResourceReader;  typedef sys::CPointer<CResourceReader>  PResourceReader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceStream;
      friend class CResourceManager;
      friend class CResourceReader;
    public:
      CResource() = default;
      virtual ~CResource() = default;
  };
  
  class CResourceStream {
      friend class CResource;
      friend class CResourceManager;
      friend class CResourceReader;
    public:
      CResourceStream() = default;
      virtual ~CResourceStream() = default;
  };
  
  class CResourceReader {
      friend class CResource;
      friend class CResourceStream;
      friend class CResourceManager;
    public:
      CResourceReader() = default;
      virtual ~CResourceReader() = default;
    public:
      virtual const char* type() const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
  };
  
  class CResourceManager {
      friend class CResource;
      friend class CResourceStream;
      friend class CResourceReader;
    protected:
      sys::CMap<sys::CString, PResourceReader> mReaders;
    public:
      CResourceManager() = default;
      virtual ~CResourceManager() = default;
    public:
      inline PResourceReader reader(const char* ext) { auto it = mReaders.find(ext); return it != mReaders.end() ? it->second : nullptr; }
      inline void            reader(PResourceReader pReader) { mReaders[pReader->type()] = pReader; }
      inline void            save(PResource) { }
  };
}

#endif //__ogl_cresource_hpp__
