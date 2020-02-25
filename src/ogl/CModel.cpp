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
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CModelManager::CModelManager() {
    // @todo: register all loaders through descriptors
    loader(new CFileModelLoader);
  }
  
  CModelManager::~CModelManager() {
    
  }
}
