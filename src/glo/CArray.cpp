#include "glo/CArray.hpp"
#include "glo/CBuffer.hpp"
#include "glo/CLayout.hpp"

namespace glo {
  CVertexArray::CVertexArray() {
    log::nfo << "glo::CVertexArray::CVertexArray()::" << this << log::end;
    GLCALL(::glGenVertexArrays(1, &mID));
  }
  
  CVertexArray::~CVertexArray() {
    log::nfo << "glo::CVertexArray::~CVertexArray()::" << this << log::end;
    GLCALL(::glDeleteVertexArrays(1, &mID));
  }
  
  void CVertexArray::bind(bool state/*=true*/) const {
    log::dbg << "glo::CVertexArray::bind(bool)::" << this << log::end;
    GLCALL(::glBindVertexArray(state ? mID : 0));
  }
  
  void CVertexArray::buffer(const CVertexBuffer& buffer, const CVertexLayout& layout) {
    log::nfo << "glo::CVertexArray::buffer(CVertexBuffer&, CVertexLayout&)::" << this << log::end;
    bind();
    buffer.bind();
    const auto& elements = layout.elements();
    GLuint      offset = 0;
    for (std::size_t i = 0; i < elements.size(); i++) {
      const auto& element = elements[i];
      const auto  stride  = layout.stride(); // FOR EACH layout.push() DO += sizeof(GLfloat) 
      GLCALL(::glEnableVertexAttribArray(i));
      // @todo: adjust for ::glVertexAttribIPointer // GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT
      // @todo: adjust for ::glVertexAttribLPointer // GL_DOUBLE
      GLCALL(::gxVertexAttribPointer(i, element.count, element.type, element.norm, stride, offset));
      offset += element.size(); // += element.count * sizeof(GLfloat)
    }
  }
}
