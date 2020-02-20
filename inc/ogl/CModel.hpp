#ifndef __ogl_cmodel_hpp__
#define __ogl_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "ogl/CResource.hpp"
#include "ogl/CMaterial.hpp"

namespace ogl {
  class CModel;        typedef sys::CPointer<CModel>        PModel; 
  class CMesh;         typedef sys::CPointer<CMesh>         PMesh; 
  class CModelManager; typedef sys::CPointer<CModelManager> PModelManager;
  class CModelStream;  typedef sys::CPointer<CModelStream>  PModelStream;
  
  // model ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMesh {
      friend class CModel;
    protected:
      PMaterial mMaterial;
      PModel    mParent;
  };
  
  class CModel : public ogl::CResource {
      friend class CMesh;
      friend class CModelManager;
      friend class CModelStream;
    protected:
      std::vector<PMesh> mMeshes;
    public:
      CModel();
      CModel(PModelStream);
      ~CModel();
    public:
      virtual void load(PModelStream) final;
  };
  
  class CModelStream : public sys::CStream {
      friend class CModel;
      friend class CModelManager;
    public:
      using sys::CStream::CStream;
  };
  
  // descriptors /////////////////////////////////////////////////////////////////////////////////////////////////////
  
  struct SModelDescriptor {
    protected: sys::CString key;
    SModelDescriptor() = default;
    ~SModelDescriptor() = default;
    virtual sys::CString getKey() const { return key; };
  };
  
  struct SShapeModelDescriptor : public SModelDescriptor {
    template <glm::EShape S> SShapeModelDescriptor(const glm::SShape<S>& shape) {
      key = shape.toString();
    }
  };
  
  struct SFileModelDescriptor : public SModelDescriptor {
    CString file;
    SFileModelDescriptor(const CString& file) : file{file} { 
      key = file;
    }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> class CModelLoader : public sys::CSingleton<CModelLoader<T>> {
    public:
      virtual PModelStream load(const T&) = 0; 
  };
  template <typename T> using PModelLoader = sys::CPointer<CModelLoader<T>>;
  
  template <> class CModelLoader<SFileModelDescriptor> : public sys::CSingleton<CModelLoader<SFileModelDescriptor>> {
    public:
      virtual PModelStream load(const SFileModelDescriptor&);
  };
  using CFileModelLoader = CModelLoader<SFileModelDescriptor>;  typedef sys::CPointer<CFileModelLoader>  PFileModelLoader;
  
  template <> class CModelLoader<SShapeModelDescriptor> : public sys::CSingleton<CModelLoader<SShapeModelDescriptor>> {
    public:
      virtual PModelStream load(const SShapeModelDescriptor&);  
  };
  using CShapeModelLoader = CModelLoader<SShapeModelDescriptor>; typedef sys::CPointer<CShapeModelLoader> PShapeModelLoader;
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> {
    public:
      CModelManager();
      ~CModelManager();
    public:
      PModel find(const sys::CString& name);
      
      template <typename T, class = typename std::enable_if<std::is_convertible<T*,SModelDescriptor*>::value>::type> PModel load(const T& sDesc, const sys::CString& name = "") {
        log::nfo << "ogl::CModelManager::load(T&,CString&)::" << this << log::end;
        
        PModelLoader<T> pLoader {CModelLoader<T>::instance()};
        PModelStream    pStream {pLoader->load(sDesc)};
        PModel          pModel  {new CModel{pStream}};
        
        
        // @todo: create key/id from descriptor
        // @todo: try to find model in cache using that key
        // @todo: else load it
        // @todo: update cache
        
        return pModel;
      }
  };
}

#endif //__ogl_cmodel_hpp__
