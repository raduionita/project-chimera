
```text
    // @todo: cell->push()
      // if element->aabb <= this->aabb // [INSIDE] // bigger than child, smaller than this->aabb
        // if element->aabb <= 1/8th space // [INSIDE CHILD] // BRANCH
          
          // @todo: check if it makes sense to split, or keep it a leaf
        
          // if NO this.children
            // this->makeChildren()
          // for each child in this->children // compare element on each child
            // if element->aabb < child->aabb
              // child->pushElement(element)
              // return
        // else // [INSIDE THIS] // intersects plane // bigger than child, smaller than this->aabb // LEAF
          // this->elements += element
          // this->minAABB += element->aabb // merge min aabb's
          // return
      // else // [OUTSIDE] // element outside this->aabb // (only on ROOT)
        // this->elements += element
        // this->aabb += element->aabb // merge aabb's
        // for each child in this->children
          // elements = child->pullElements()
          // this->elements += elements
        // this->makeChildren() // OR repurpose
        // for each element in this->elements // move
          // for each child in this->children
            // child->pushElement(element)
            // this->elements -= element // remove element from this->elements
        // return
```

```c++
      // split
      glm::real fX {mAABB.max.x - mAABB.min.x}, hX {fX/2}; 
      glm::real fY {mAABB.max.y - mAABB.min.y}, hY {fY/2}; 
      glm::real fZ {mAABB.max.z - mAABB.min.z}, hZ {fZ/2}; 
      glm::aabb tLDB {/*min*/mAABB.min.x,   mAABB.min.y,   mAABB.min.z,   /*max*/mAABB.min.x+hX,mAABB.min.y+hY,mAABB.min.z+hZ};
      glm::aabb tRDB {/*min*/mAABB.min.x+hX,mAABB.min.y,   mAABB.min.z,   /*max*/mAABB.max.x,   mAABB.min.y+hY,mAABB.min.z+hZ};
      glm::aabb tLTB {/*min*/mAABB.min.x,   mAABB.min.y+hY,mAABB.min.z,   /*max*/mAABB.min.x+hX,mAABB.max.y,   mAABB.min.z+hZ};
      glm::aabb tRTB {/*min*/mAABB.min.x+hX,mAABB.min.y+hY,mAABB.min.z,   /*max*/mAABB.max.x,   mAABB.max.y,   mAABB.min.z+hZ};
      glm::aabb tLDF {/*min*/mAABB.min.x,   mAABB.min.y,   mAABB.min.z+hZ,/*max*/mAABB.min.x+hX,mAABB.min.y+hY,mAABB.max.z};
      glm::aabb tRDF {/*min*/mAABB.min.x+hX,mAABB.min.y,   mAABB.min.z+hZ,/*max*/mAABB.max.x,   mAABB.min.y+hY,mAABB.max.z};
      glm::aabb tLTF {/*min*/mAABB.min.x,   mAABB.min.y+hY,mAABB.min.z+hZ,/*max*/mAABB.min.x+hX,mAABB.max.y,   mAABB.max.z}; 
      glm::aabb tRTF {/*min*/mAABB.min.x+hX,mAABB.min.y+hY,mAABB.min.z+hZ,/*max*/mAABB.max.x,   mAABB.max.y,   mAABB.max.z};
```

```text
      // @todo: re-push
      // for each stored node in this.mNodes
          // re-push
    
        
    // @todo: cell->pull()
      // elements = this->elements;
      // for each child in this->children
        // elements += child->pullElements()
      // return elements
```
      
