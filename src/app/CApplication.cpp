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
#include "ogl/CModel.hpp"

#include "glm/glm.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CVector.hpp"

namespace app {
  int CApplication::exec() {
    log::nfo << "app::CApplication::exec()::" << this << log::end;
  
    init();
    
    app::CEditWindow* pMain    {new app::CEditWindow};
    uix::CSurface*    pSurface {new uix::CSurface(pMain, uix::EWindow::VISIBLE)};
    
    attach(this,    uix::EEvent::KEYDOWN,     &app::CApplication::onKeydown);
    attach(pSurface,uix::EEvent::RESIZE,      &uix::CRender::onResize);
    
    pMain->title(pSurface->version());
    pMain->show();
    pSurface->current();
    
    GLCALL(::glEnable(GL_BLEND));
    GLCALL(::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    auto    area {pSurface->area()};
    
    log::nfo << "app::CApplication::exec()::" << this << " w:" << area.w << " h:" << area.h << log::end;
  
    // @todo: rectangle model builder here
    // ogl::PModelManager man {ogl::CModelManager::instance()};
    // ogl::PModel        mdl {man->load(glm::rectangle{1.f})};
    
    // ogl::CEngine::getInstance()->getModelManger()->
    // ogl::CModelManager::instance()->load(sys::CFile{""});
    ogl::PModel mdl = ogl::CModelManager::instance()->load(glm::rect{});
    
    GLfloat vertices[] {-0.5f,-0.5f,+0.0f, 0.0f,0.0f,  // 0 // bottom-left
                        +0.5f,-0.5f,+0.0f, 1.0f,0.0f,  // 1 // bottom-right
                        +0.5f,+0.5f,+0.0f, 1.0f,1.0f,  // 2 // top-right
                        -0.5f,+0.5f,+0.0f, 0.0f,1.0f}; // 3 // top-left
    GLuint  indices [] {0,1,2, 2,3,0};
  
    ogl::CVertexArray   vao;
    ogl::CDataBuffer    vbo {vertices, 4 * 5, ogl::CDataBuffer::VERTEX}; // 4 vertices * 5 components (xyzuv)
    ogl::CVertexLayout  vlo;
    vlo.push({GL_FLOAT, 3});
    vlo.push({GL_FLOAT, 2});
    vao.buffer(vbo, vlo);
    ogl::CDataBuffer    ibo {indices, 2 * 3, ogl::CDataBuffer::INDEX}; // 2 triangles * 3 vertices
  
    // @todo: ogl::PShaderManager man {ogl::CShaderManager::instance()}
    ogl::CShader         shd {"../../res/shaders/simple/perspective.hlsl"};
    
    ogl::PTextureManager man {ogl::CTextureManager::instance()};
    ogl::PTexture        tx1 {man->load(sys::file("../../res/textures/notfound.dds"), "notfound")};
    
    vao.bind(false);
    shd.bind(false);
    ibo.bind(false);
    vbo.bind(false);
    
    float     r {0.0f};
    glm::mat4 M {1.0f};
    glm::mat4 V {glm::lookat({+0.0f,+0.0f,-2.0f}, {0.0f,0.0f,0.0f}, glm::Y)};
    glm::mat4 P {glm::perspective(60.f, float(area.w), float(area.h), 1.f, 1000.f)};
    // glm::mat4 P = glm::ortho(-2.0f,2.0f, -2.0f,2.0f, -1.f,+1.f);
    
    while (runs()) {
      GLCALL(::glClearColor(0.1f,0.1f,0.1f,1.f));
      GLCALL(::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
      
      glm::loop(r, 1.f, 0.f, 360.f);
      
      log::nfo << "app::CApplication::exec()::" << this << " LOOP" << log::end;
  
      shd.bind(true);
      shd.uniform("u_sTexture", tx1);
      shd.uniform("u_mMVP", P*V*M*glm::rotate(r,glm::Y));
      shd.uniform("u_mM", M);
      shd.uniform("u_mV", V);
      shd.uniform("u_mP", P);
      
      vao.bind(true);
      ibo.bind(true);
      
      // @todo: pRenderSystem->render(CDrawable);
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
