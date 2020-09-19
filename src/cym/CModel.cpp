#include "cym/CModel.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  CModel::CModel() {
    log::nfo << "cym::CModel::CModel()::" << this << log::end;
  }
  
  CModel::CModel(CModelInfo& info) {
    log::nfo << "cym::CModel::CModel(CModelInfo)::" << this << log::end;
    load(info);
  }
  
  CModel::~CModel() {
    log::nfo << "cym::CModel::~CModel()::" << this << log::end;
    // @todo: delete meshes
    // @todo: delete vaos
    // @todo: delete vbos
    // @todo: delete ibos
  }
  
  void CModel::load(CModelInfo&) {
    log::nfo << "cym::CModel::load(SModelInfo)::" << this << log::end;
    
    // @todo: glstuff
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CModelManager::CModelManager() : cym::CResourceManager("model") {
    // @todo: register all loaders through descriptors
    log::nfo << "cym::CModelManager::CModelManager()::" << this << log::end;
    loader(new CFileModelLoader);
  }
  
  CModelManager::~CModelManager() {
    log::nfo << "cym::CModelManager::~CModelManager()::" << this << log::end;
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CFileModelLoader::CFileModelLoader() : TModelLoader<sys::CFile>() {
    log::nfo << "cym::CFileModelLoader::CFileModelLoader()::" << this << log::end;
    // @todo: move this to engine/code init 
    codec(new COBJCodec);
  }  
  
  CFileModelLoader::~CFileModelLoader() {
    log::nfo << "cym::CFileModelLoader::~CFileModelLoader()::" << this << log::end;
  }
  
  PCodec CFileModelLoader::codec(const sys::CString& ext) { 
    auto it = mCodecs.find(ext);
    if (it != mCodecs.end()) { return it->second; }
    return nullptr;
  }
  
  void CFileModelLoader::load(cym::CFileModelInfo& info) {
    sys::CFile& file {info.source};
    log::nfo << "cym::CFileModelLoader::load(TModelInfo<sys::CFile>&)::" << this << " FILE:" << file << log::end;
    
    // @todo: refactor this into a static-cached call for codec
    PCodec pCodec = codec(file.ext());
    
    // PModelData pData = sys::static_pointer_cast<PModelData::type>(pCodec->decode(file));; 
    
    pCodec->decode(info);
    
    log::nfo << "cym::CFileModelLoader::load(TModelInfo<sys::CFile>&)::" << this << "::file.loader::done" << file << log::end;
  }
}





class CVertex {
  public:
    // float x,y,z;   // position
    // float t,s;     // texcoord // u,v;
    // float x,y,z;   // normal
    // float x,y,z;   // tangent
    // float x,y,z;   // binormal
    // int   a,b,c,d; // bones (bone ids)
    // float a,b,c,d; // weights (bone weights)
};

class CTriangle {
  public:
    int mIndices[3];
};

class CMeshData {
  public:
    sys::block<CVertex> mVertice;
    union {
      sys::block<int>       mIndices;
      sys::block<CTriangle> mTriangles;
    }; // indices
    //CMaterialData mMaterial;
};

class CModelData {
  public:
    sys::block<CMeshData> mMeshes;
};

