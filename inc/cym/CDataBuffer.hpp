#ifndef __cym_cbuffer_hpp__
#define __cym_cbuffer_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CObject.hpp"

namespace cym {
  class CBuffer : public CObject  {
    public:
      enum EType {NONE,VERTEX,INDEX,TEXTURE,PIXEL,UNIFORM,TRANSFORM,READ,WRITE};
    protected:
      GLenum  mTarget;
      bool    mInited {false};
    public:
      using CObject::CObject;
  };
  
  class CDeviceBuffer : public CBuffer {
    public:
      enum EAccess {READ,WRITE,READWRITE,NONE=READWRITE,BOTH=READWRITE};
    protected:
      void*   mBuffer {nullptr};
      GLenum  mAccess;
    public:
      using CBuffer::CBuffer;
    public:
      CDeviceBuffer(EType type, EAccess access = EAccess::READWRITE) {
        CYM_LOG_NFO("cym::CDeviceBuffer::CDeviceBuffer()::" << this);
        mTarget = type == EType::VERTEX ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
        mAccess = access == EAccess::WRITE ? GL_WRITE_ONLY : access == EAccess::READ ? GL_READ_ONLY : GL_READ_WRITE;
        GLCALL(::glGenBuffers(1, &mID));
        GLCALL(::glBindBuffer(mTarget, mID));
        mBuffer = ::glMapBuffer(mTarget,mAccess);
      }
    
// @todo: check if buffer (by target) is bound
      
      template<typename T> void data(T* data, bool flush = false) {
        CYM_LOG_NFO("cym::CDeviceBuffer::data(T*,bool)::" << this);
        ::memcpy(mBuffer, data, sizeof(T));
        if (flush)
          ::glUnmapBuffer(GL_ARRAY_BUFFER);
      }
  };
  
  class CDataBuffer : public CBuffer {
      friend class CVertexArray;
    protected:
      GLcount  mCount  {0};
      GLintptr mOffset {0};
      GLsize   mSize   {0};
    public:
      using CBuffer::CBuffer;
    public:
      CDataBuffer();
      template<typename T> CDataBuffer(const T* pData, GLsize nSize, GLcount nCount=1, EType eType=EType::NONE, GLenum eUsage=GL_STATIC_DRAW) { 
        CYM_LOG_NFO("cym::CDataBuffer::CDataBuffer(T*," << nSize << ",EType,GLenum)::" << this);
        assert(nSize != 0 && "CDataBuffer CANNOT be size=0!");
        mSize   = nSize;
        mCount  = nCount;
        mOffset = pData ? nSize : 0;
        mInited = pData != 0;
        mTarget = eType == EType::VERTEX ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
        GLCALL(::glGenBuffers(1, &mID));
        GLCALL(::glBindBuffer(mTarget, mID));
        GLCALL(::glBufferData(mTarget, nSize, pData, eUsage));
      }
      CDataBuffer(GLsize nSize, GLcount nCount=1, EType eType=EType::NONE, GLenum eUsage=GL_STATIC_DRAW) : CDataBuffer((const void*)(0),nSize,nCount,eType,eUsage) { }
      ~CDataBuffer();
    public:
      template<typename T> inline GLcount data(const T* pData, GLsize nSize) { 
        CYM_LOG_NFO("cym::CDataBuffer::data(" << "T*," << nSize << ")::" << this);
        assert(mInited == false && "CDataBuffer was constructed with data, can't add more!");
        if (nSize == 0) 
          return mOffset;
        GLCALL(::glBufferSubData(mTarget, mOffset, nSize, pData));
        return mOffset += nSize;
      }
             GLcount data(cym::CGeometryInput*);
      inline GLcount count() const { return mCount; }
      inline void bind(bool bState = true) const { GLCALL(::glBindBuffer(mTarget, bState ? mID : 0));  }
  };
  
  class CVertexBuffer : public CDataBuffer {
    public:
      template<typename T> CVertexBuffer(const T* pData, GLsize nSize, GLcount nCount=1, GLenum eUsage=GL_STATIC_DRAW) : CDataBuffer(pData,nSize,nCount,EType::VERTEX,eUsage) {
        CYM_LOG_NFO("cym::CVertexBuffer::CVertexBuffer(T*,"<< nSize <<","<< nCount <<",GLenum)::" << this);
      }
      CVertexBuffer(GLsize nSize, GLcount nCount=1, GLenum eUsage=GL_STATIC_DRAW) : CDataBuffer((const void*)(0),nSize,nCount,EType::VERTEX,eUsage) { }
      ~CVertexBuffer() { CYM_LOG_NFO("cym::CVertexBuffer::~CVertexBuffer()::" << this); }
  };
  
  class CIndexBuffer : public CDataBuffer {
    public:
      template<typename T> CIndexBuffer(const T* pData, GLsize nSize, GLcount nCount = 1, GLenum eUsage=GL_STATIC_DRAW) : CDataBuffer(pData,nSize,nCount,EType::INDEX,eUsage) {
        CYM_LOG_NFO("cym::CIndexBuffer::CIndexBuffer(T*,"<< nSize <<","<< nCount <<",GLenum)::" << this);
      }
      CIndexBuffer(GLsize nSize, GLcount nCount=1, GLenum eUsage=GL_STATIC_DRAW) : CDataBuffer((const void*)(0),nSize,nCount,EType::INDEX,eUsage) { }
      ~CIndexBuffer() { CYM_LOG_NFO("cym::CIndexBuffer::~CIndexBuffer()::" << this); }
  };
  
  class CTriangleBuffer : public CIndexBuffer {
    public:
      template<typename T> CTriangleBuffer(const T* pData, GLsize nSize, GLcount nCount=3, GLenum eUsage=GL_STATIC_DRAW) : CIndexBuffer(pData,nSize,nCount,eUsage) {
        CYM_LOG_NFO("cym::CTriangleBuffer::CTriangleBuffer(T*,"<< nSize <<","<< nCount <<",GLenum)::" << this);
      }
      CTriangleBuffer(GLsize nSize, GLcount nCount=3, GLenum eUsage=GL_STATIC_DRAW) : CIndexBuffer((const void*)(0),nSize,nCount,eUsage) { }
      ~CTriangleBuffer() { CYM_LOG_NFO("cym::CTriangleBuffer::~CTriangleBuffer()::" << this); }
  };
  
  // range /// 
  
  class CBufferRange {
    protected:
      GLuint mStart;
      GLuint mCount;
    public:
      CBufferRange() : mStart(0), mCount(0) { }
      CBufferRange(GLuint start, GLuint count) : mStart(start), mCount(count) { }
      ~CBufferRange() = default;
    public:
      inline GLuint getStart() const { return mStart; }
      inline GLuint getCount() const { return mCount; }
  };
}

#endif //__cym_cbuffer_hpp__
