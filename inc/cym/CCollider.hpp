#ifndef __cym_ccollider_hpp__
#define __cym_ccollider_hpp__

#include "cym/cym.hpp"
#include "cym/CSkeleton.hpp"
#include "glm/CAABB.hpp"

namespace cym {

// @todo: build using (and around) skeleton joints(bones) - create a bbox around each bone, intersection is tested..
// @todo: ..tested using these bbox(es) not the actual mesh
// @todo: when mesh is read, use min/max vertices around a joint to determine size of the collider's bbox(es)

// @todo: types of shapes: aabb, volume, rectangular parallelipiped, pill (semi-spehere + cillinder + semi-sphere)

  class CCollider {
    protected:
      glm::CAABB           mAABB;
      sys::wpo<CGeometry>    mGeometry;
      sys::wpo<CSkeleton> mSkeleton;
  };
}

#endif //__cym_ccollider_hpp__
