#ifndef __cym_ccontroller_hpp__
#define __cym_ccontroller_hpp__

namespace cym {
  class CController {
    
  };
  
  // @todo: camera controller
    // fps // this example is for a LH coordicate system, needs adjustment
      // on KEY UP // go in the direction of the target/forward
        // camera.position += camera.target * camera.speed
      // on KEY DOWN // go opposite to the target/forward
        // camera.position -= camera.target * camera.speed
      // on KEY LEFT // strafe left
        // left = camera.target * camera.up
        // left = normalize(left)
        // left *= camera.speed
        // camera.position += left
      // on KEY RIGHT // strafe right
        // right = camera.up * camera.target
        // right = normalize(right)
        // right *= camera.speed
        // camera.position += right
      // on KEY PAGE_UP // like a hellicopter
        // camera.position.y += camera.speed
      // on KEY PAGE_DOW // like a hellicopter
        // camera.position.y -= camera.speed
        
        
}

#endif //__cym_ccontroller_hpp__
