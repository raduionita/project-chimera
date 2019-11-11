#include "app/CApplication.hpp"
#include "app/CEditWindow.hpp"

#include "uix/CLoop.hpp"
#include "uix/CEvent.hpp"
#include "uix/CSurface.hpp"
#include "uix/CPanel.hpp"
#include "uix/CLayout.hpp"
#include "uix/CButton.hpp"

#include "ogl/CBuffer.hpp"
#include "ogl/CArray.hpp"
#include "ogl/CLayout.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CTexture.hpp"

#include "glm/glm.hpp"

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
    
    GLfloat2 vertices[] {{-0.5f,-0.5f},{+0.5f,-0.5f},{+0.5f,+0.5f},{-0.5f,+0.5f}};
    GLuint   indices [] {0,1,2, 2,3,0};
  
    ogl::CVertexArray   vao;
    ogl::CVertexBuffer  vbo {vertices, 4 * 2 * sizeof(GLfloat)};
    ogl::CVertexLayout  vlo;
    vlo.push({GL_FLOAT, 2});
    vao.buffer(vbo, vlo);
    ogl::CIndexBuffer   ibo {indices, 6};
  
  //ogl::CShaderLoader csl;
  //ogl::PShader       shd {csl.load("name")}
    ogl::CShader       shd {"../../res/shaders/simple/color.csl"};
    
    ogl::PTexture      tex = ogl::CTextureManager::load("../../res/textures/monster.dds");
    
    vao.bind(false);
    shd.bind(false);
    ibo.bind(false);
    vbo.bind(false);
    
    float r = 0.0f;
    
    while (runs()) {
      pSurface->clear();
      
      log::nfo << "app::CApplication::exec()::" << this << " LOOP" << log::end;
  
      shd.bind(true);
      shd.sampler("u_sTexture", tex);
      shd.uniform("u_vColor", glm::loop(r,0.05f,0.f,1.f),0.7f,0.2f,1.0f);
      
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
