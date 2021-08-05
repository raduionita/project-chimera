#ifndef __cym_ccluster_hpp__
#define __cym_ccluster_hpp__

#include "cym/cym.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CDrawable.hpp"

namespace cym {
  class CCluster { };
  
// @todo: these are things that can be bundled/clustered tougheter
// @todo: like CGeometry, CParticle or whatever...for batch rendering
  
  template<typename T> class TCluster : public cym::CCluster { // CGeometryCluster, CParticleCluster
      
  }; 
  
  class CGeometryCluster : public cym::TCluster<cym::CGeometry>, public cym::CDrawable {
      
  };
  
  // class CParticleCluster : public cym::TCluster<cym::CParticle>, public cym::CDrawable {
  //    
  // };
}

#endif //__cym_ccluster_hpp__
