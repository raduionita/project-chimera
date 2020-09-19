#ifndef __cym_cnode_hpp__
#define __cym_cnode_hpp__

#include "sys/CPointer.hpp"
#include "sys/CBlock.hpp"
#include "sys/CLogger.hpp"
#include "sys/CException.hpp"
#include "cym/cym.hpp"

namespace cym {  
  class CNode { };
  
  template<typename T> class TNode : public CNode {
    public:
      typedef T type;
    protected:
      sys::TPointer<T> mResource;
    public:
      TNode(sys::TPointer<T> r) : mResource{r} { }
      virtual ~TNode() { log::nfo << "cym::TNode::~TNode()::" << this << log::end; }
  };
}


#endif //__cym_cnode_hpp__
