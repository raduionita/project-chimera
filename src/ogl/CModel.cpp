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
  
  CModel::CModel(PModelStream stream) {
    load(stream);
  }
  
  void CModel::load(PModelStream stream) {
    
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PModelStream CModelLoader<SFileModelDescriptor>::load(const SFileModelDescriptor &sDesc) {
    CModelStream* pStream {new CModelStream};
    
    // @todo: which file opener?! md5 obj 3ds dae fxb xml?!
    
    // @todo: open file, read file
    
    
    return pStream;
  }
  
  PModelStream CModelLoader<SShapeModelDescriptor>::load(const SShapeModelDescriptor &sDesc) {
    CModelStream* pStream {new CModelStream};
    
    
    
    return pStream;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CModelManager::CModelManager() {
    // @todo: register all loaders through descriptors
  }
  
  CModelManager::~CModelManager() {
    
  }
}
