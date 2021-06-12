#include "cym/CVertexLayout.hpp"
#include "cym/CGeometry.hpp"

namespace cym {
  inline void CVertexLayout::push(SElement&& element) {
    // CYM_LOG_NFO("cym::CVertexLayout::push(GLenum,c:"<< components << ",c:" << count << ",GLubyte)::" << this);
    assert((mType == EType::SEQUENTIAL && element.count > 1) || (mType == EType::INTERLEAVED && element.count == 1) && "count doesnt match getLayout");
    mElements.push_back(std::move(element));
    mStride += element.components * ::glEnumToSize(element.type); 
  }
      
  inline void CVertexLayout::push(EAttribute eAttrib, GLenum type, GLcount components, GLcount count, GLubyte norm) {
    // CYM_LOG_NFO("cym::CVertexLayout::push(GLenum,c:"<< components << ",c:" << count << ",GLubyte)::" << this);
    assert(((mType == EType::SEQUENTIAL && count > 1) || (mType == EType::INTERLEAVED && count == 1)) && "count doesnt match getLayout");
    mElements.push_back({eAttrib, type, components, count, norm}); 
    mStride += components * ::glEnumToSize(type); 
  }
  
  void CVertexLayout::read(cym::CGeometryInput* in) {
    push({in->attribute(), in->type(), in->width(), in->count()});
  }
}
