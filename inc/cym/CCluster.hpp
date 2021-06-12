#ifndef __cym_ccluster_hpp__
#define __cym_ccluster_hpp__

#include "cym/cym.hpp"
#include "cym/CModel.hpp"
#include "cym/CDrawable.hpp"

namespace cym {
  class CCluster { };
  
// @todo: these are things that can be bundled/clustered tougheter
// @todo: like CModel, CParticle or whatever...for batch rendering
  
  template<typename T> class TCluster : public cym::CCluster { // CModelCluster, CParticleCluster
      
  }; 
  
  class CModelCluster : public cym::TCluster<cym::CModel>, public cym::CDrawable {
      
  };
  
  // class CParticleCluster : public cym::TCluster<cym::CParticle>, public cym::CDrawable {
  //    
  // };
}

#endif //__cym_ccluster_hpp__
