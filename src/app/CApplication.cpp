#include "app/CApplication.hpp"
#include "app/CEditWindow.hpp"

#include "uix/CLoop.hpp"
#include "uix/CEvent.hpp"
#include "uix/CSurface.hpp"
#include "uix/CPanel.hpp"
#include "uix/CLayout.hpp"
#include "uix/CButton.hpp"

#include "ogl/CBuffer.hpp"
#include "ogl/CVertexArray.hpp"
#include "ogl/CLayout.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CTexture.hpp"

#include "glm/CMatrix.hpp"
#include "glm/CVector.hpp"

namespace app {
  int CApplication::exec() {
    log::nfo << "app::CApplication::exec()::" << this << log::end;
  
    init();
    
    // mEngine->textureManager()->loader(new CDdsLoader);
    
    app::CEditWindow* pMain   {new app::CEditWindow};
    uix::CBoxLayout*  pLayout {new uix::CBoxLayout(uix::ELayout::VERTICAL)};
    
    uix::CSurface* pSurface = pLayout->add(new uix::CSurface(pMain, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    uix::CPanel*   pPanel   = pLayout->add(new uix::CPanel(pMain, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    uix::CButton*  pButton  = new uix::CButton(pPanel, "RESIZE", {50,50,90,40});
    
    pPanel->style()->background(uix::SColor{33,33,33});
    
    attach(this,    uix::EEvent::KEYDOWN,     &app::CApplication::onKeydown);
    attach(pPanel,  uix::EEvent::COMMAND,     &app::CApplication::onCommand);
    attach(pButton, uix::EEvent::LBUTTONDOWN, &app::CApplication::onClick);
    attach(pSurface,uix::EEvent::RESIZE,      &uix::CRender::onResize);
    
    pMain->layout(pLayout);
    pMain->title(pSurface->version());
    pMain->show();
    
    pSurface->current();
    
    GLCALL(::glEnable(GL_BLEND));
    GLCALL(::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    GLfloat vertices[] {-0.5f,-0.5f, 0.0f,0.0f,  // 0 // bottom-left
                        +0.5f,-0.5f, 1.0f,0.0f,  // 1 // bottom-right
                        +0.5f,+0.5f, 1.0f,1.0f,  // 2 // top-right
                        -0.5f,+0.5f, 0.0f,1.0f}; // 3  // top-left
    GLuint  indices [] {0,1,2, 2,3,0};
  
    ogl::CVertexArray   vao;
    ogl::CDataBuffer    vbo {vertices, 4 * 4, ogl::CDataBuffer::VERTEX}; // 4 vertices * 4 components (xyuv)
    ogl::CVertexLayout  vlo;
    vlo.push({GL_FLOAT, 2});
    vlo.push({GL_FLOAT, 2});
    vao.buffer(vbo, vlo);
    ogl::CDataBuffer    ibo {indices, 2 * 3, ogl::CDataBuffer::INDEX}; // 2 triangles * 3 vertices
  
    ogl::CShader         shd {"../../res/shaders/simple/texture.hlsl"};
    ogl::PTextureManager man {ogl::CTextureManager::instance()};
    ogl::PTexture        tx1 {man->load(sys::CFile("../../res/textures/notfound.dds"), "notfound")};
    
    vao.bind(false);
    shd.bind(false);
    ibo.bind(false);
    vbo.bind(false);
    
    float     r = 0.0f;
    glm::mat4 m;
    
    
    
    log::nfo << m << log::end;
    
    while (runs()) {
      GLCALL(::glClearColor(0.1f,0.1f,0.1f,0.f));
      GLCALL(::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
      
      log::nfo << "app::CApplication::exec()::" << this << " LOOP" << log::end;
  
      shd.bind(true);
      shd.uniform("u_vColor", glm::loop(r,0.05f,0.f,1.f),0.7f,0.2f,1.0f);
      tx1->filtering(ogl::CTexture::EFiltering::TRILINEAR);
      tx1->wrapping(ogl::CTexture::EWrapping::REPEAT);
      shd.uniform("u_sTexture", tx1);
  
      vao.bind(true);
      ibo.bind(true);
      
      GLCALL(::glDrawElements(GL_TRIANGLES, ibo.count(), GL_UNSIGNED_INT, GL_NULL));
      
      pSurface->swap();
      poll();
    }
  
    DELETE(pMain);

    free();
    
    return 0;
  }
  
  void CApplication::onKeydown(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onKeydown(CEvent*)::" << this << " K:" << pEvent->key() << log::end;
    
    switch (pEvent->key()) {
      case 'Q'      : quit(0); break;
      case VK_ESCAPE: quit(0); break;
      case VK_F5    : break;
      case VK_F11   : pEvent->target()->fullscreen(); break;
    }
  }
  
  void CApplication::onClick(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY() << log::end;
  
    quit(0);
  }
  
  void CApplication::onCommand(uix::CEvent* pEvent) {
    log::nfo << "app::CApplication::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()) << log::end;
    
  }
}

DECLARE_APPLICATION(app::CApplication);
