#ifndef __cym_cscene_hpp__
#define __cym_cscene_hpp__

#include "sys/CPointer.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CNode.hpp"

namespace cym {
  class CScene; typedef sys::sptr<cym::CScene> PScene;
  class CNode;  typedef sys::sptr<cym::CNode>  PNode;
  
  class CScene {
    protected:
      sys::map<uint,PNode> mNodes;
  };
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CNodeManager : public cym::CResourceManager {
    public:
      template<typename T> PNode load(const sys::string& name, const T& from) {
        //     <model file="../path/to/model.ext"> // entity      // PModel = CModelManager::init(file)
        //       
        //     <model>
        
        
        
        
        
        // ::init(CModel::SDescriptor) -> NNode<CModel>
          // find model
            // PModel pModel = CModelManager::mModels[zName]
            // NNode  oNode  = NNode<CModel>(pModel)                  // update NNode w/ CModel data (meshes)
          // make model
            // CModel::SDescriptor = CFileModelLoader::init(CFile);
            // ? = CShapeModelLoader::init(glm::shape);
            // ? = CDataModelLoader::init(data);
            // PModel pModel = new CModel(CModel::SDescriptor);
            // NNode  oNOde  = NNode<CModel>(pModel)                  // update NNode w/ CModel data (meshes)
          // apply stuff from CModel::SDescriptor FIELDS to oNode
            // meshes for each mesh
              // ::load(SMesh::SDescriptor)
                // 
          // return oNode;
        
        
        
        
        return nullptr;        
      }
  };
  
  class CSceneManager : public cym::CResourceManager {
    protected:
      sys::map<sys::string,cym::PScene> mScenes;
    public:
    template<typename T> PScene load(const sys::string& name, const T& from) {
      CYM_LOG_NFO("cym::CSceneManager::load(CString&,T&)::" << this);
      
      // structure
      // <node:scene name="exterior">
      //   <node:model name="" file="../path/to/model.ext" />
      //   // or
      //   <node:model>                                       // NModel = CNodeManager::load(TNodeInfo<CModel>)
      //     <model file="../path/to/model.ext"> // entity      // PModel = CModelManager::load(file)
      //       <meshes>
      //         <mesh>
      //           <material />
      //         </mesh>
      //       </meshes>
      //     <model>
      //   </node:model>                                      // add PModel to NModel
      // </node:scene>
    
      return nullptr;
    }
  };
}

#endif //__cym_cscene_hpp__
