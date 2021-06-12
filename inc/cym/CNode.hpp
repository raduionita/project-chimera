#ifndef __cym_cnode_hpp__
#define __cym_cnode_hpp__

#include "sys/CPointer.hpp"
#include "sys/CBlock.hpp"
#include "sys/CLogger.hpp"
#include "sys/CException.hpp"
#include "cym/cym.hpp"

namespace cym {
  class CNode;  typedef sys::sptr<cym::CNode>  PNode;
  
  class CNode { };
  
  template<typename T> class TNode : public CNode {
    public:
      typedef T type;
    protected:
      sys::sptr<T> mResource;
    public:
      TNode(sys::sptr<T> r) : mResource{r} { }
      virtual ~TNode() { CYM_LOG_NFO("cym::TNode::~TNode()::" << this); }
  };
  
  // class NTexture : public TNode<cym::CTexture> {
  //   protected:
  //     cym::PChannel mResource;
  // };
  
  // class NChannel : public TNode<cym::CChannel> {
  //   protected:
  //   //cym::PChannel mResource;
  // };
  
  // class NMaterial : public TNode<cym::CMaterial> {
  //   protected:
  //     sys::CCollection<NChannel> mChannels;
  // };
}


#endif //__cym_cnode_hpp__
