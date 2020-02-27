#include "ogl/CModel.hpp"

namespace ogl {
  CModel::CModel() {
    
  }
  
  CModel::~CModel() {
    // @todo: delete meshes
    // @todo: delete vaos
    // @todo: delete vbos
    // @todo: delete ibos
  }
  
  CModel::CModel(PModelStream pStrem) {
    
  }
  
  void CModel::load(PModelStream pStrem) {
    
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CModelManager::CModelManager() {
    // @todo: register all loaders through descriptors
    loader(new CFileModelLoader);
  }
  
  CModelManager::~CModelManager() {
    
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PModelStream CFileModelLoader::load(const sys::CFile &file) {
    log::nfo << "ogl::CFileModelLoader::load(CFile&)::" << this << " FILE:" << file << log::end;
    CModelStream* pStream {new CModelStream};  
    
    
    // @todo: use the file extension to get/create a file codec
    
    // @todo: use the codec to load the model stream
    
    return pStream;
  }
}
