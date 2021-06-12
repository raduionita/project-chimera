#ifndef __cym_cgeometry_hpp__
#define __cym_cgeometry_hpp__

#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CVertexLayout.hpp"
#include "glm/CVector.hpp"

#include <algorithm>
#include <unordered_map>

namespace cym {
  class CGeometry;
  
  class CGeometryInput {
      friend class CGeometry;
    public:
      typedef EVertexAttribute EAttribute; 
      typedef uint32_t         count_type;
    public:
      CGeometryInput() = default;
      virtual ~CGeometryInput() = default;
    public:
      virtual inline EAttribute  attribute() const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_type  stride()    const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_type  size()      const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline bool        empty()     const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_type  count()     const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline const void* data()      const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline GLenum      type()      const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline count_type  width()     const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual inline void        push(const void*) { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
  };
  
  template<typename T, CGeometryInput::EAttribute A, GLenum E, uint W> class TGeometryInput : public CGeometryInput {
      friend class CGeometry;
    public:
      typedef CGeometryInput::EAttribute EAttribute; 
      typedef T value_type;
    protected:
      std::vector<T> mInput;
    public: // ctors
      using CGeometryInput::CGeometryInput;
    public: // operators
      value_type& operator [](count_type i) { return mInput[i]; }
      void        operator +=(T&& v) { mInput.push_back(std::move(v)); }
    public: // cats
      operator       T*()       { return static_cast<T*>(mInput.data()); }
      operator const T*() const { return static_cast<const T*>(mInput.data()); }
    public: // 
      virtual inline EAttribute  attribute() const   override { return A; }
      virtual inline count_type  stride()    const   override { return sizeof(T); }
      virtual inline count_type  size()      const   override { return mInput.size() * sizeof(T); }
      virtual inline bool        empty()     const   override { 
        return mInput.size() == 0; 
      }
      virtual inline count_type  count()     const   override { return mInput.size(); }
      virtual inline const void* data()      const   override { return static_cast<const void*>(mInput.data()); }
      virtual inline GLenum      type()      const   override { return E; }
      virtual inline count_type  width()     const   override { return W; }
      virtual inline void        push(const void* v) override { const T* p = static_cast<const T*>(v); mInput.push_back(*p); }
              inline void        push(T&& v)                  { mInput.push_back(std::move(v)); }
              inline void        push(const T& v)             { mInput.push_back(v); }
              inline T&          next()                       { return mInput.emplace_back(T{}); }
              inline void        grow(count_type n)           { mInput.resize(n); }
  };
  
  class CGeometryStream {
      friend class CModel;
      friend class CGeometry;
    public:
      typedef CGeometryInput::count_type count_type;
    protected:
      std::map<sys::string,CGeometryInput*> mInputs; // positions, normals, texcoords, texcoords2 (multi material), binormals...
    public:
      virtual ~CGeometryStream() { for (auto& in : mInputs) delete in.second; }
    public:
      CGeometryInput* operator[](const sys::string& name) { auto it = mInputs.find(name); if (it != mInputs.end()) return it->second; throw sys::exception("Input "+ name + " NOT FOUND!",__FILE__,__LINE__); }
    public:
      const CGeometryInput* const find(const sys::string& name) const { auto it = mInputs.find(name); if (it != mInputs.end()) return it->second; return nullptr; }
      
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CGeometryInput*>::value>::type> T& create(sys::string&& name, T*&& in)  { mInputs.insert({std::move(name), std::move(in)}); return *in; }
      // inputs
      
      inline               count_type count() const    { return mInputs.begin()->second->count(); }
      inline               count_type size()  const    { count_type s = 0; for (auto& in : mInputs) s += in.second->size(); return s; }
      inline               void       pack()           { 
        for (auto it = mInputs.begin(); it != mInputs.end(); ) {
          if (it->second == nullptr || it->second->empty()) {
            delete it->second;
            mInputs.erase(it++);
          } else {
            ++it;
          }
        }
      }
  };
  
  class CGeometryLayout {
      friend class CGeometry;
    public:
      typedef uint32_t                   value_type;
      typedef CGeometryInput::count_type count_type;
    protected:
      std::vector<value_type> mIndices; // int[] // int array
    public:
      value_type& operator[](count_type i)  { assert(i < mIndices.size() && "out of bounds"); return mIndices[i]; }
    public:
      operator const value_type*() const { return static_cast<const value_type*>(mIndices.data()); }
      operator const void*()       const { return static_cast<const void*>(mIndices.data()); }
    public:
      inline std::vector<value_type>& indices() { return mIndices; }
      inline count_type  count() const      { return mIndices.size(); }
      inline count_type  size()  const      { return mIndices.size() * sizeof(value_type); }
      inline void        push(value_type v) { mIndices.push_back(v); }
      inline void push(const std::initializer_list<value_type>& tValues) { mIndices.reserve(mIndices.size() + tValues.size()); std::copy(tValues.begin(), tValues.end(), std::back_inserter(mIndices)); }
      inline const void* data()  const      { return static_cast<const void*>(mIndices.data()); }
  };
  
  class CGeometry {
      friend class CModel;
      friend class CModelLoader;
    protected:
      CGeometryStream mStream;
      CGeometryLayout mLayout;
    public:
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CGeometryInput*>::value>::type> T& input(std::string&& name, T*&& in) { return mStream.create(std::move(name), std::move(in)); }
      inline CGeometryStream& stream()                    { return mStream; } 
      inline decltype(CGeometryStream::mInputs)& inputs() { return mStream.mInputs; } 
      inline CGeometryLayout& layout()                    { return mLayout; }
      inline decltype(CGeometryLayout::mIndices)& indices() { return mLayout.mIndices; }
      inline void             pack()                      { mStream.pack(); }
  };
  
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::POSITION, GL_FLOAT,3> CPositionInput;  // float[3][n] // vec3[n]
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::NORMAL,   GL_FLOAT,3> CNormalInput;
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::COLOR,    GL_FLOAT,3> CColorInput;
  typedef TGeometryInput<glm::vec2, CGeometryInput::EAttribute::TEXCOORD, GL_FLOAT,2> CTexcoordInput;
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::TANGENT,  GL_FLOAT,3> CTangentInput;
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::BINORMAL, GL_FLOAT,3> CBinormalInput;
  typedef TGeometryInput<glm::uvec3,CGeometryInput::EAttribute::JOINTS,   GL_UINT, 3> CJointsInput;    // uint[3][n]
  typedef TGeometryInput<glm::vec3, CGeometryInput::EAttribute::WEIGHTS,  GL_FLOAT,3> CWeightsInput;
}

#endif //__cym_cgeometry_hpp__
