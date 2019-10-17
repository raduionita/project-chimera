#include "glo/CArray.hpp"
#include "glo/CBuffer.hpp"
#include "glo/CLayout.hpp"

namespace glo {
  CArray::CArray() {
    GLCALL(::glGenVertexArrays(1, &mID));
  }
  
  CArray::~CArray() {
    GLCALL(::glDeleteVertexArrays(1, &mID));
  }
  
  void CArray::bind(bool state/*=true*/) const {
    GLCALL(::glBindVertexArray(state ? mID : 0));
  }
  
  void CArray::buffer(const CBuffer& buffer, const CLayout& layout) {
    bind();
    buffer.bind();
    const auto& elements = layout.elements();
    GLuint      offset = 0;
    for (std::size_t i = 0; i < elements.size(); i++) {
      const auto& element = elements[i];
      const auto  stride  = layout.stride(); // FOR EACH layout.push() DO += sizeof(GLfloat) 
      GLCALL(::glEnableVertexAttribArray(i));
      GLCALL(::glVertexAttribPointer(i, element.count, element.type, element.norm, stride, (GLvoid*)(offset)));
      offset += element.size(); // += element.count * sizeof(GLfloat)
    }
  }
}
