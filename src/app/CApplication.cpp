#include "app/CApplication.hpp"
#include "app/CEditWindow.hpp"

#include "uix/CLoop.hpp"
#include "uix/CEvent.hpp"
#include "uix/CSurface.hpp"
#include "uix/CPanel.hpp"
#include "uix/CLayout.hpp"
#include "uix/CButton.hpp"
#include "uix/CDialog.hpp"
#include "uix/CContext.hpp"

#include "cym/CCore.hpp"
#include "cym/CShader.hpp"
#include "cym/CTexture.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CScene.hpp"

#include "glm/glm.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CVector.hpp"
#include "glm/CTransform.hpp"
#include "glm/CFrustum.hpp"

namespace app {
  void CApplication::exec() {
    SYS_LOG_NFO( "app::CApplication::exec()::" << this);
    
// @todo: onInit
    app::CEditWindow* pMain    {new app::CEditWindow};
    
    uix::CContext*    pContext {new uix::CContext{}};

    /*uix::CButton* */mCamS = new uix::CButton{pMain,"CAMS",uix::SSize{120,40}};
    uix::CButton*     pExit  {new uix::CButton{pMain,"EXIT",uix::SSize{40,40}}};
    
    uix::CSurface*    pRight {new uix::CSurface{pMain, pContext}};
    
    uix::CBoxLayout*  pTopMenu {new uix::CBoxLayout{uix::ELayout::HORIZONTAL,uix::SSize{uix::AUTO,50}}};
    pTopMenu->add(mCamS); // @todo: on resize the second button (or TItem) runs to the right
    
    uix::CBoxLayout*  pLeftMenu {new uix::CBoxLayout{uix::ELayout::VERTICAL,uix::SSize{50,uix::AUTO}}};
    pLeftMenu->add(pExit);
     
    uix::CBoxLayout*  pContent {new uix::CBoxLayout{uix::ELayout::HORIZONTAL}};
    pContent->add(pLeftMenu);
    pContent->add(pRight);
    
// @todo: multiple surfaces
  //pContent->add(new uix::CLayout::CGap{ });
  //pContent->add(pLeft); // left surface
    
    uix::CBoxLayout*  pLayout  {new uix::CBoxLayout{uix::ELayout::VERTICAL}};
    pLayout->add(pTopMenu);
    pLayout->add(pContent);
// @todo: fix getting & setting area/rect, use mArea to return getArea(), and set mArea on setArea(), @see CWindow::area() & CLayout::area()
    pMain->layout(pLayout); // pLayout->apply(pMain);
    
    attach(this,  uix::CEvent::KEYDOWN, &app::CApplication::onKeydown);
    attach(this,  uix::CEvent::COMMAND, &app::CApplication::onCommand);
    
    pMain->show();
    pContext->vsync(true);
    pContext->current(pRight);
    
    cym::CCore::load();
    
    auto tArea {pRight->area()};
    
    SYS_LOG_NFO("tArea" << tArea);
    
    cym::CCore::getRenderSystem()->setViewport(0,0,tArea.w,tArea.h);
  
    // return;
    
    // mGrid = new app::CGrid{app::CGrid::XZ, 1.f};
    
    auto shd {cym::CShader{"../../res/shaders/simple/perspective.hlsl"}};
    
// @todo: NULL geometry (when geo failed loading or doesnt exist) + wrapped inside IGeometry + reason why it failed 
// @todo: NULL material
// @todo: NULL shader
// @todo: NULL (all) resource types
// @todo: create/init/load NULL texture on engine init/load // all geo w/o textures use the NULL texture
    auto t01 {cym::CCore::getTextureManager()->load(cym::null{}, 32u)};
         t01->setWrapping(cym::CTexture::EWrapping::CLAMP_TO_EDGE);
         
  //auto mdl {cym::CCore::getGeometryManager()->load(sys::file{"../../res/models/ambulance/Ambulance.dae"}, cym::CGeometryManager::EOption::VERTICES)};
    
    auto scn {cym::CCore::getSceneManager()->load("scene")};
  
    auto n00 {new cym::NModel{cym::CCore::getGeometryManager()->load(glm::rect{20.f,20.f}, 5u, glm::Y, cym::CGeometry::DEFAULT)}};
    auto n0x {new cym::NModel{cym::CCore::getGeometryManager()->load(glm::cube{2.f}, 2u, cym::CGeometry::DEFAULT)}};
    auto n0y {new cym::NModel{cym::CCore::getGeometryManager()->find(n0x->getGeometry()->getName())}};
    auto n0z {new cym::NModel{cym::CCore::getGeometryManager()->find(n0x->getGeometry()->getName())}};
    auto c00 {new cym::NCamera{glm::vec3{0.f, 0.f,-1.f}, 90.f, (glm::real(tArea.w)/glm::real(tArea.h)), 0.1f,  10.f}};
    auto c01 {new cym::NCamera{glm::vec3{0.f}          ,100.f, (glm::real(tArea.w)/glm::real(tArea.h)), 0.1f, 100.f}};
    auto cxx = c00;
    
// @todo: 2 cameras 2 viewports

    
    scn->push(n00, glm::xform{glm::vec3{ 0.0f,-1.0f, 0.0f}});
    scn->push(n0x, glm::xform{glm::vec3{-1.0f, 0.0f, 0.0f}}); // w/ transform structure
    scn->push(n0y, glm::xform{glm::vec3{ 0.0f,-1.0f, 0.0f}});
    scn->push(n0z, glm::xform{glm::vec3{ 0.0f, 0.0f,-1.0f}});
    
    auto s04 = scn->push(c00, glm::xform{glm::vec3{ 0.0f, 5.0f, 5.0f}});
    auto s05 = scn->push(c01, glm::xform{glm::vec3{10.0f,15.0f,15.0f}});
    
    auto n0f {new cym::NModel{cym::CCore::getGeometryManager()->load(c00->getFrustum())}};
    auto s0f = scn->push(n0f);
    
// @todo: (edit mode): when loading nodes/models/lights/etc. create their debug geometry & separate them (so they're toggable)
// @todo: (game mode): when loading entities don't load debug stuff
    
// @todo: matrix/transform w/ controller: update on loop, when u get the matrix it's already up to date
    
    SYS_LOG_NFO("scene:" << (scn));
    
// @todo: add (debug) elements (grid,gizmo)
      
// @todo: onTick
    glm::uint nFPS{0u};
    glm::mat4 M  {1.0f};
    glm::mat4 V;
    glm::mat4 P;
    
    while (runs()) {
      //SYS_LOG_NFO("loop");
      
// @todo: [INPUT] process input & events
      
      poll();
      
      cxx = mCamA == 0 ? c00 : c01;
      
      s05->orbit({0.f},1.f,glm::Y);
      
// @todo: [UPDATE] update the scene
  // process ASYNC what ai/resorce loading...
      
      cym::fps(nFPS);
      pMain->title("VERSION:" + std::string(pContext->version()) + " | FPS:" + std::to_string(nFPS));
      
      V = cxx->getV();
      P = cxx->getP();
  
// @todo: [RENDER] scene

// @todo: managers should (have a say in) enable/disable OGL stuff, like:
  // CMaterialManager::disableBlending()
  // CMaterialManager::setColor()

// @todo: setup redering state & clear stuff up
      GLCALL(::glClearColor(0.1f,0.1f,0.1f,1.f));
      GLCALL(::glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
      
// @todo: models = snc->find(CQuery{MODEL})
// @todo: lights = scn->find(CQuery{LIGHT});
// @todo: camera = ?
  
// @todo: shadow-map/light-map phase
  // for each light : lights
    // set light render state
    // set FBO for shadow map
    // for each model : moodels
      // draw model (from the position of the light)
    
// @todo: drawable phase
  // set model render state
  // for each model : models
    // draw model  
    
// @todo: debug phase
  // draw  grid, gizmo + bbox(es)...
      
// @todo: pRenderSystem->render(CDrawable);
  // tDrawable.vao.bind(true);
  // tDrawable.ibo.bind(true);
  // GLCALL(::glDrawElements(GL_TRIANGLES, tDrawable.ibo.count(), GL_UNSIGNED_INT, GL_NULL));
      
// @todo: proper scene CQuery here
      auto tResult {scn->find({})};
      auto tModels {tResult->getModels()};
      for (auto& tNode : tModels) {
        auto pGeometry {tNode->getGeometry()};
        
        //SYS_LOG_NFO("draw:" << tGeometry->getName());
        
        // M compiles reading all getMatix() 'till root OR node:scene
        M = tNode->getMatrix();
  
        shd.bind(true);
        shd.uniform("u_sTexture", t01);
        shd.uniform("u_mPVM", P*V*M/* * vertex */);
        
        GLSWITCH((pGeometry->getFlags() & cym::CGeometry::EFlag::CCW), ::glFrontFace(GL_CCW), ::glFrontFace(GL_CW));
        
        pGeometry->draw();
      }
  
  
      GLCALL(::glFlush());
      
// @todo: CWindow::update()
      pContext->swap();
      
// @todo: cache (and reuse) last fbo if no chanes/updates to the scene (or visible objects) 

// @todo: lower resolution on camera (fast) move/spin // if camera orbit keep object at that point at full rez.
      
  
      // quit();
    }
    
// @todo: insert model to scene after the scene has been created, dynamically, like: CApplication::onOpenFile()...
    //uix::CFileDialog* pDialog {new uix::CFileDialog{{"*.*","*.txt"}}};
    // if (pDialog->show()) {
    //   SYS_LOG_NFO( "app::CApplication::exec()::" << this << " " << pDialog->getFile());
    //   
    //   scn->push(mdl);
    // }
    
// @todo: onFree
    DELETE(pMain);
    
    
    
    ///////////////////////////////////////////////////
    
// @todo: EDITOR: start (w/ project file)
      // create window
        // opengl,vulkan,directx
      // init core
        // managers & codecs
        // renderer (compile/load all shaders or shader components)
      // load ASYNC scene from project file (returns empty scene)
      // create virtual camera (not bound to the scene tree) 
      // create virtual grid (not bound to the scene tree)
      // create virtual gizmo (scale,rotate,move)
      
// @todo: LOOP
// @todo: input (win32)
        // read/listen for inputs (canvas/opengl window) into a bucket of inputs (do not process them right away)
          // onMouseClick => push new CCommand(select element)
          // onMouseMove => push new CCommand(move/scale/rotate selected element by...)
// @todo: update
        // compute all commands
          // (from dialog)  command the opens scene file and merges w/ current (probably empty) one
          // (from dialog)  command that opens new model file and adds it to scene root (ASYNC) (starts as an empty model)
          // (from ai )     command move scene nodes
          // (from network) command move scene nodes
          // (from inputs)  command move scene nodes (node:scene OR node:joint)
            // update node.position (or matrix)
            // if node.cell.AABB & node.AABB match
              // no octree canges
            // else check w/ parent cell (and so on)
              // update node's cell // node.cell = node.cell.parent 
            // if node exists root cell 
              // (scene reset) add it to COctree::mDangling
          // (from button)  create box => (ASYNC) create model using glm::cube{} (model starts empty) 
        // update scenes
          // refresh scene state
            // update screen octree
              // if octree.isDirty (has dangling)
                // octree.refresh/repartition
// @todo: render
        // draw grid (under all other elements)
        // get all (available) scene elements (using a frustum query)
        // set camera (scene or virtual)
        // for each element 
          // draw element 
            // if element ready
              // draw model
            // else
              // draw debug (spinner) at origin
          // draw debug (bbox) 
            // draw bbox (if selected)
            // draw icon (lightbulb,emitter,force) 
        // draw gizmo
        // post-processing pass (bloom, ao, color,...)
    
    
    
    
    
    
    
    
    
    SYS_LOG_NFO( "app::CApplication::exec()::" << this << " end");
  }
  
  void CApplication::onKeydown(uix::CEvent* pEvent) {
    SYS_LOG_NFO("app::CApplication::onKeydown(CEvent*)::" << this << " K:" << pEvent->key());
    
    switch (pEvent->key()) {
      case 'Q'      : quit(0); break;
      case VK_ESCAPE: quit(0); break;
      case VK_F5    : break;
      case VK_F11   : pEvent->target()->fullscreen(); break;
    }
  }
  
  void CApplication::onClick(uix::CEvent* pEvent) {
    SYS_LOG_NFO("app::CApplication::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY());
  
    quit(0);
  }
  
  void CApplication::onCommand(uix::CEvent* pEvent) {
    SYS_LOG_NFO("app::CApplication::onCommand(CEvent*)::" << this << " T:" << pEvent->target());
    
    if (pEvent->control() == mCamS)
      mCamA = (mCamA + 1) % 2;
    else 
      quit(0);
  }
}

DECLARE_APPLICATION(app::CApplication);
