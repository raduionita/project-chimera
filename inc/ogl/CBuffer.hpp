#ifndef __ogl_cbuffer_hpp__
#define __ogl_cbuffer_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CObject.hpp"

namespace ogl {
  class CBuffer : public CObject {
    public:
      using CObject::CObject;
  };
  
  class CDataBuffer : public CBuffer {
    public:
      enum EType {VERTEX,INDEX};
    public:
      using CBuffer::CBuffer;
    protected:
      GLcount mCount;
      GLenum  mTarget;
    public:
      CDataBuffer();
      template <typename T> CDataBuffer(const T* data, GLcount count, EType type, GLenum usage = GL_STATIC_DRAW) { 
        log::nfo << "ogl::CDataBuffer::CDataBuffer(T*,GLcount,GLenum,GLenum)::" << this << log::end;
        mCount  = count;
        mTarget = type == EType::VERTEX ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
        GLCALL(::glGenBuffers(1, &mID));
        GLCALL(::glBindBuffer(mTarget, mID));
        GLCALL(::glBufferData(mTarget, count * sizeof(T), data, usage));
      }
      ~CDataBuffer();
    public:
      inline GLcount count() const { return mCount; }
      inline void bind(bool state = true) const { GLCALL(::glBindBuffer(mTarget, state ? mID : 0));  }
  };
}

#endif //__ogl_cbuffer_hpp__
