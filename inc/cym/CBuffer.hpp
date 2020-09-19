#ifndef __cym_cbuffer_hpp__
#define __cym_cbuffer_hpp__

#include "cym/cym.hpp"
#include "CObject.hpp"

namespace cym {
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
      template<typename T> CDataBuffer(const T* data, GLcount count, EType type, GLenum usage = GL_STATIC_DRAW) { 
        log::nfo << "cym::CDataBuffer::CDataBuffer(T*,GLcount,EType,GLenum)::" << this << log::end;
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
  
  class CVertexBuffer : public CDataBuffer {
    public:
      template<typename T> CVertexBuffer(const T* data, GLcount count, GLenum usage = GL_STATIC_DRAW) : CDataBuffer(data,count,EType::VERTEX,usage) {
        log::nfo << "cym::CVertexBuffer::CVertexBuffer(T*,GLcount,GLenum)::" << this << log::end;
      }
  };
  
  class CIndexBuffer : public CDataBuffer {
    public:
      template<typename T> CIndexBuffer(const T* data, GLcount count, GLenum usage = GL_STATIC_DRAW) : CDataBuffer(data,count,EType::INDEX,usage) {
        log::nfo << "cym::CIndexBuffer::CIndexBuffer(T*,GLcount,GLenum)::" << this << log::end;
      }
  };
  
  class CTriangleBuffer : public CIndexBuffer {
    public:
      template<typename T> CTriangleBuffer(const T* data, GLcount count, GLenum usage = GL_STATIC_DRAW) : CIndexBuffer(data, count*3, usage) {
        log::nfo << "cym::CTriangleBuffer::CTriangleBuffer(T*,GLcount,GLenum)::" << this << log::end;
      }
  };
}

#endif //__cym_cbuffer_hpp__
