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
  class CResourceLoader;  typedef sys::CPointer<CResourceLoader>  PResourceLoader;
  class CResourceBuilder; typedef sys::CPointer<CResourceBuilder> PResourceBuilder;
  
  // template <typename T> class CResourceBuilder { 
  //     virtual PResourceStream from(const T&) = 0;
  // };
  //
  // template <typename T> class CTextureBuilder : public CResourceBuilder<T> {
  //    
  // };
  //
  // class CFileTextureBuilder : public CTextureBuilder<sys::CFile> {
  //   protected:
  //     sys::CVector<CTextureLoader*> mLoaders;
  //   public:
  //     PResourceStream from(const sys::CFile&) = 0;
  // };
  
  class CResource { // loadable entity/file/object
      friend class CResourceManager;
      friend class CResourceStream;
    public:
      
  };
  
  class CResourceStream {
      friend class CResource;
      friend class CResourceLoader;
      friend class CResourceManager;
    public:
      CResourceStream() = default;
      virtual ~CResourceStream() = default;
  };
  
  class CResourceLoader {
      friend class CResource;
      friend class CResourceManager;
      friend class CResourceStream;
    public:
      CResourceLoader() = default;
      virtual ~CResourceLoader() = default;
    public:
      virtual inline bool able(const std::any&) const = 0;
  };
  
  class CResourceBuilder {
    public:
      CResourceBuilder() = default;
      virtual ~CResourceBuilder() = default;
    public:
      virtual inline sys::CString type() const = 0;
  };
  
  class CResourceManager {
      friend class CResource;
      friend class CResourceStream;
      friend class CResourceLoader;
    protected:
      sys::CVector<PResourceBuilder> mBuilders;
    public:
      CResourceManager();
      virtual ~CResourceManager();
    public:
      template <typename T, class = typename std::enable_if<std::is_base_of<ogl::CResourceBuilder,T>::value>::type> const T* builder(T* pBuilder) {
        // move loader to list of loaders
        mBuilders.push_back(pBuilder);
        // return inserted
        return mBuilders.back().ptr();
      }
      inline sys::CVector<PResourceBuilder>::value_type builder(const sys::CString& type) { 
        for (auto& pBuilder : mBuilders) {
          if (type.compare(pBuilder->type()) == 0) {
            return pBuilder;
          }
        }
        throw sys::CException("Missing CTextureLoader for '"+ type +"'", __FILE__, __LINE__);
      }
      inline const sys::CVector<PResourceBuilder>& builders() const { return mBuilders; }
  };
}

#endif //__ogl_cresource_hpp__
