#include "cym/CVertexArray.hpp"
#include "cym/CDataBuffer.hpp"
#include "cym/CVertexLayout.hpp"

namespace cym {
  CVertexArray::CVertexArray() {
    SYS_LOG_NFO("cym::CVertexArray::CVertexArray()::" << this);
    GLCALL(::glGenVertexArrays(1, &mID));
  }
  
  CVertexArray::~CVertexArray() {
    SYS_LOG_NFO("cym::CVertexArray::~CVertexArray()::" << this);
    GLCALL(::glDeleteVertexArrays(1, &mID));
  }
  
  void CVertexArray::bind(bool state/*=true*/) const {
    log::dbg << "cym::CVertexArray::bind(bool)::" << this << log::end;
    GLCALL(::glBindVertexArray(state ? mID : 0));
  }
  
  void CVertexArray::load(CDataBuffer& buffer, CVertexLayout& layout) {
    SYS_LOG_NFO("cym::CVertexArray::load(CDataBuffer&, CVertexLayout&)::" << this);
    bind();
    buffer.bind();
    
    const auto& elements = layout.elements();
    GLuint      offset = 0;
    const auto  stride = layout.stride(); // FOR EACH layout.push() DO += sizeof(GLfloat)
    
    for (const auto& element : elements) {
      GLCALL(::glEnableVertexAttribArray(element.attribute));
      
      SYS_LOG_NFO("cym::CVertexArray::load(CDataBuffer&, CVertexLayout&)::" << this << " type=" << element.type << "|offset=" << offset);
      
      switch (element.type) {
        default:
        case GL_FLOAT : GLCALL(::gxVertexAttribPointer(element.attribute, element.components, element.type, element.norm, stride, offset)); break;
        case GL_DOUBLE: GLCALL(::gxVertexAttribLPointer(element.attribute, element.components, element.type, stride, offset)); break;
        case GL_BYTE  : 
        case GL_UBYTE :
        case GL_SHORT :
        case GL_USHORT:
        case GL_INT   :
        case GL_UINT  : GLCALL(::gxVertexAttribIPointer(element.attribute, element.components, element.type, stride, offset)); break;
      }
      offset += element.size(); // += element.count * sizeof(GLfloat)
      // offset += element.size();   // += components * sizeof(GLfloat)
      // offset += element.offset(); // += count * components * sizeof(GLfloat)
    }
    
    // SYS_LOG_NFO("cym::CVertexArray::load(CDataBuffer&, CVertexLayout&)::" << this << "::DONE");
  }
}

/* Each attribute is sequential, batched in a single VBO.
 * 
 * (xyzxyzxyz... rgbrgb... ststst...), 
 * 
    GLfloat vertices[] = {
     -0.5f, 0.0f, 0.0f,  0.5f, 0.0f, 0.0f,  0.0f, 0.5f, 0.0f,  // xyzxyzxyz // 3x3=9 position
      1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // rgbrgbrgb // 3x3=9 color
      0.0f, 0.0f,        1.0f, 0.0f,        1.0f, 1.0f     };  // ststst    // 3x2=6 texture coordinate

    // vao + vbo here...
    
    //  0 = stride = 0 //
    //  0 = offset = 0                                  // where positions start
    
    // specifiy position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0)); // stride can aslo be 3 * sizeof(GL_FLOAT)
    glEnableVertexAttribArray(0);
    
    //  9 = offset += 9 // * sizeof(GL_FLOAT) = 36      // where colors start
    
    // specify color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(9 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    
    // 18 = offset += 9 // * sizeof(GL_FLOAT) = 72      // where texcoords start
    
    // specify texture coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(18 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    
    // 18 = offset += 9 // * sizeof(GL_FLOAT) = 72      // done
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    VBOIdVec.push_back(VBOId);
 */

/* Interleaved attribute in a single VBO
 *  
 *  (xyzrgbstxyzrgbst...),
 *
    GLfloat vertices[] = {
     -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // xyzrgbast =  8 components = 8
      0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // xyzrgbast = +8 components = 16
      0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f};  // xyzrgbast = +8 components = 24

    // vao + vbo here...
    
    // 8 = stride = 8 // * sizeof(GL_FLOAT) = 24
    // 0 = offset = 0 // * sizeof(GL_FLOAT) =  0
    
    // specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(0));
    glEnableVertexAttribArray(0);
    
    // 3 = offset += 3 // 3 components per position            
    
    // specify color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),(GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    // 6 = offset += 3 // 3 components per color 
    
    // specify texture coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2); 

    // 8 = offset += 2 // 2 components per texcoord
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    VBOIdVec.push_back(VBOId);
 */
