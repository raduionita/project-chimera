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
#include "cym/CModel.hpp"
#include "cym/CCamera.hpp"

#include "glm/glm.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CVector.hpp"
#include "glm/CTransform.hpp"

namespace app {
  void CApplication::exec() {
    CYM_LOG_NFO( "app::CApplication::exec()::" << this);
    
// @todo: onInit
    app::CEditWindow* pMain    {new app::CEditWindow};
    
    uix::CContext*    pContext {new uix::CContext{}};
    
    uix::CButton*     pPush  {new uix::CButton{pMain,"PUSH",uix::SSize{120,40}}};
    uix::CButton*     pSave  {new uix::CButton{pMain,"SAVE",uix::SSize{120,40}}};
    uix::CPanel*      pLeft  {new uix::CPanel{pMain}};
    uix::CSurface*    pRight {new uix::CSurface{pMain, pContext}};
    
    uix::CBoxLayout*  pTopMenu {new uix::CBoxLayout{uix::ELayout::HORIZONTAL,uix::SSize{uix::AUTO,50}}};
    pTopMenu->add(pPush);
    pTopMenu->add(pSave); // @todo: on resize the second button (or TItem) runs to the right
    
    uix::CBoxLayout*  pContent {new uix::CBoxLayout{uix::ELayout::HORIZONTAL}};
    pContent->add(pLeft);
    pContent->add(pRight);
    
    uix::CBoxLayout*  pLayout  {new uix::CBoxLayout{uix::ELayout::VERTICAL}};
    pLayout->add(pTopMenu);
    pLayout->add(pContent);
    
    pMain->layout(pLayout); // pLayout->apply(pMain);
    
    attach(this,     uix::CEvent::EType::KEYDOWN, &app::CApplication::onKeydown);
    
    pMain->show();
    pContext->vsync(true);
    pContext->current(pRight);
    
    cym::CCore::load();
    
    // render system flags/states
    GLCALL(::glEnable(GL_BLEND));
    GLCALL(::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // backface culling
    GLCALL(::glDisable(GL_CULL_FACE));
    GLCALL(::glCullFace(GL_BACK));
    GLCALL(::glFrontFace(GL_CCW));
    // depth test
    GLCALL(::glEnable(GL_DEPTH_TEST));
    GLCALL(::glDepthFunc(GL_LEQUAL));
    GLCALL(::glDepthMask(GL_TRUE));
    
    auto    area {pRight->area()};
  
    CYM_LOG_NFO("app::CApplication::exec()::" << this << " pTopMenu.area " << pTopMenu->area());
    CYM_LOG_NFO("app::CApplication::exec()::" << this << " pContent.area " << pContent->area());
    CYM_LOG_NFO("app::CApplication::exec()::" << this << " pLeft.area " << pLeft->area());
    CYM_LOG_NFO("app::CApplication::exec()::" << this << " pRight.area " << pRight->area());
    CYM_LOG_NFO("app::CApplication::exec()::" << this << " pMain.area " << pMain->area());
  
    
// @todo: test (online) if quaternion rotation works
    
    // return;
    
    auto shd {cym::CShader{"../../res/shaders/simple/perspective.hlsl"}};
    
// @todo: find a way to have instances w/o TInstance,
  // resources dont hold pointers to other resources, just ids // model::meshes, material::channels[n]::texture
    
  //auto mdl {cym::CCore::getModelManager()->load(sys::CFile{"../../res/models/ambulance/Ambulance.dae"}, cym::CModelManager::EOption::VERTICES)};
    auto g01 {cym::CCore::getGeometryManager()->load(glm::rect{8.f, 8.f}, 2u, glm::Y, cym::CModel::EFlag::DEFAULT)};
    auto g02 {cym::CCore::getGeometryManager()->load(glm::cube{2.f}, 2u, cym::CModel::EFlag::DEFAULT)};
    auto t01 {cym::CCore::getTextureManager()->load(sys::CFile{"../../res/textures/notfound.bmp"})};
         t01->getTexture().setWrapping(cym::CTexture::EWrapping::REPEAT);
         
    auto scn {cym::CCore::getSceneManager()->load(sys::CFile{"../res/scenes/default.scene"})};
    scn->push(g01/*,pos=0*/);
    scn->push(g02, glm::xform{glm::vec3{5.f}, glm::quat{0.f, 0.f, 60.f}}); // w/ transform structure
    
    
    
    
    
// @todo: push node to scene
// @todo: camera is a node in a scene
// @todo: camera types: scene, editor(virtual,cannot be accessed outside editor), debug(can see what other cameras have in their view frustum, cannot be accessed outside editor)
// 


// @todo: (edit mode): when loading nodes/models/lights/etc. create their debug geometry & separate them (so they're toggable)
// @todo: (game mode): when loading entities don't load debug stuff











    
// @todo: matrix/transform w/ controller: update on loop, when u get the matrix it's already up to date
    
    CYM_LOG_NFO("scene:" << (scn->getScene()));
    
// @todo: add (debug) elements (grid,gizmo)
      
// @todo: onTick
    glm::uint nFPS{0u};
    glm::real r {0.0f};
    glm::mat4 M {1.0f};
    
// @todo: camera
  //auto cam {sys::spt<CCamera>{new CCamera{ 60.f... }}};
    glm::mat4 V {glm::lookat({0.f,10.f,20.f}, {0.f,0.f,0.f}, glm::Y)};
    glm::mat4 P {glm::perspective(60.f, float(area.w), float(area.h), 1.f, 11.f)};
    glm::mat4 PV {P*V};
    
    glm::frustum f{PV};
  
    CYM_LOG_NFO("P:" << P);
    CYM_LOG_NFO("V:" << V);
    CYM_LOG_NFO("PV:" << PV);
    CYM_LOG_NFO("frustum:" << f);
    
    
    while (runs()) {
      CYM_LOG_NFO("loop");
      
// @todo: [INPUT] process input & events
      
      poll();
      
// @todo: [UPDATE] update the scene
  // process ASYNC what ai/resorce loading...
      
      cym::fps(nFPS);
      pMain->title("VERSION:" + std::string(pContext->version()) + " | FPS:" + std::to_string(nFPS));
  
      glm::loop(r, 1.f, 0.f, 360.f); // w/ every call 0 will get closer to 360, then loop-back
      
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
  // draw gizmo + bbox(es)...
      
// @todo: pRenderSystem->render(CDrawable);
  // tDrawable.vao.bind(true);
  // tDrawable.ibo.bind(true);
  // GLCALL(::glDrawElements(GL_TRIANGLES, tDrawable.ibo.count(), GL_UNSIGNED_INT, GL_NULL));
      
      auto tResult = scn->find({/* @todo: proper scene CQuery here */});
      for (auto& tNode : tResult->getModelNodes()) {
        auto tModel = tNode->getModel();
        
        CYM_LOG_NFO("draw:" << tModel->getName());
        
        // M compiles reading all getMatix() 'till root OR node:scene
        M = tNode->getMatrix();
  
        shd.bind(true);
        shd.uniform("u_sTexture", t01);
        shd.uniform("u_mMVP", P*V*M/* *glm::rotate(r,glm::Y)*/);
        shd.uniform("u_mM", M);
        shd.uniform("u_mV", V);
        shd.uniform("u_mP", P);
        
        tModel->draw();
      }
      
// @todo: CWindow::update()
      pContext->swap();
  
      // quit();
    }
    
// @todo: insert model to scene after the scene has been created, dynamically, like: CApplication::onOpenFile()...
    //uix::CFileDialog* pDialog {new uix::CFileDialog{{"*.*","*.txt"}}};
    // if (pDialog->show()) {
    //   CYM_LOG_NFO( "app::CApplication::exec()::" << this << " " << pDialog->getFile());
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
    
    
    
    
    
    
    
    
    
    CYM_LOG_NFO( "app::CApplication::exec()::" << this << " end");
  }
  
  void CApplication::onKeydown(uix::CEvent* pEvent) {
    CYM_LOG_NFO("app::CApplication::onKeydown(CEvent*)::" << this << " K:" << pEvent->key());
    
    switch (pEvent->key()) {
      case 'Q'      : quit(0); break;
      case VK_ESCAPE: quit(0); break;
      case VK_F5    : break;
      case VK_F11   : pEvent->target()->fullscreen(); break;
    }
  }
  
  void CApplication::onClick(uix::CEvent* pEvent) {
    CYM_LOG_NFO("app::CApplication::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY());
  
    quit(0);
  }
  
  void CApplication::onCommand(uix::CEvent* pEvent) {
    CYM_LOG_NFO("app::CApplication::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()));
  }
}

DECLARE_APPLICATION(app::CApplication);
