#ifndef __cym_cvertexlayout_hpp__
#define __cym_cvertexlayout_hpp__

#include "cym/cym.hpp"
#include "sys/CPointer.hpp"

#include <vector>

namespace cym {
  class CVertexLayout; typedef sys::sptr<CVertexLayout> PVertexLayout;
  
  enum EVertexAttribute : int { ATTRIBUTE = -1, POSITION = 0, TEXCOORD, NORMAL, COLOR, TANGENT, BINORMAL, JOINTS, WEIGHTS, ATTRIBUTE_8 };
  
  class CVertexLayout { // @see [morpheus] CBufferRange
      friend class CVertexArray;
      friend class CModel;
      friend class CGeometry;
    public:
      typedef EVertexAttribute EAttribute; 
      enum EType { NONE, SEQUENTIAL, INTERLEAVED, };
      struct SElement {
        // fields
        EAttribute attribute  {EVertexAttribute::ATTRIBUTE};
        GLenum     type       {GL_FLOAT};  // GL_FLOAT
        GLcount    components {0};
        GLcount    count      {1}; // for how many vertices
        GLubyte    norm       {GL_FALSE};  // [0|1]
        // methods
        inline  GLsize size() const { return count * components * ::glEnumToSize(type); }
      };
    protected:
      EType                 mType   {EType::NONE};
      GLsize                mStride {0};
      sys::vector<SElement> mElements;
    public:
      CVertexLayout(EType eType = EType::NONE) : mType{eType} { };
      ~CVertexLayout() { CYM_LOG_NFO("cym::CVertexLayout::~CVertexLayout()::" << this); }
    public:
      inline void push(SElement&& element);
      inline void push(EAttribute eAttrib, GLenum type, GLcount components, GLcount count=1, GLubyte norm=GL_FALSE);
             void read(cym::CGeometryInput*);
    public:
      inline GLuint                       stride()   const { return mType == EType::INTERLEAVED ? mStride : 0; }
      inline const std::vector<SElement>& elements() const { return mElements; }
  };
}

#endif //__cym_cvertexlayout_hpp__
