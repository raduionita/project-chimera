#ifndef __glo_hpp__
#define __glo_hpp__

#include "../glc/glc.hpp"

namespace glo {
  class CCamera;
  class CBuffer;
  class CLayout;
  class CArray;
  class CRenderer;
}

// on make
// p[] = {-0.5,-0.5, +0.5,-0.5, +0.5,+0.5, -0.5,+0.5} // vertex.positions
// e[] = {0,1,2, 1,2,0};                              // indices(elements)
// CArray        a;
// CIndexBuffer  i(e, 6)
// CVertexBuffer b(p, 4 * 2 * sizeof(GLfloat));
// CLayout       l;
// l.push({GL_FLOAT, 2, GL_FALSE}); // 2 floats per vertex position
// a.buffer(b,l)

// on draw
// a.bind()
// i.bind()
// ::glDrawElements(GL_TRIANGLES,i.count(),GL_UNSIGNED_INT,GL_NULL)

#endif //__glo_hpp__
