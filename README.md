
    // for what system?
      // windows/linux/...
    
    // where will you draw?
      // context?

    // how will you draw?
      // renderer

    // what will you draw?
      // application


### application
    // [app:game:console]
    // cym::CTarget + 
    //   uix::CConsole fullscreen|windowed)
    //   cym::CScreen
    //     cym::CLayer (intro)
    //       cym::CSurface
    //     cym::CLayer (loading)

    // [app:game:window]
    // cym::CTarget
    //   uix::CCanvas (fullscreen|windowed)  
    //   cym::CScreen + 
    //     cym::CLayer (intro)
    //       cym::CSurface
    //     cym::CLayer (loading)
    //     cym::CLayer (menu)
    //     cym::CLayer (scene/game)
    //     cym::CLayer (game-gui)
    //     cym::CLayer (console)
    //     cym::CLayer (debug)

### constructor
    // [app:edit:window]
    // uix::CFrame (windowed)
    //   uix::CSection
    //     cym::CScreen + uix::CCanvas
    //       cym::CLayer (scene)
    //       cym::CLayer (edit-gui)
    //       cym::CLayer (debug)
    //   uix::CPanel (buttons)
    //   uix::CStatus (statusbar)
    // uix::CPopup (preview,floating)
    //   cym::CScreen + cym::CWindow : uix::CCanvas
    //     cym::CLayer (scene)

### [edit:init]
    //    init context
    //    init window(s)
    //    init physics engine
    //    init render engine(s)
    //    load scene
### [game:init]
    //    init context
    //    init window (fullscreen)
    //    init render engine(s)
    //      CContext // CConsoleContext // COpenglContext // CWindowContext
    //      CRenderEngine <- CContext
    //      CRaycastRenderer <- CRenderEngine
    //      CPixelRenderer <- CRenderEngine
    //    init screens: splash + intro + menu(main) + loading + game
    //      start game
    //    init physics engine
    //    load scene
    //    
### [game:loop]
    //    [update]
    //      [update:inputs]
    //        cym::CInputManager::update()   // read all inputs from the user // queue a command in the CCommandSystem
    //        cym::CNetworkManager::update() // read all messages from the network
    //      [update:systems]
    //        cym::CCommandSystem::update() // executes queued commands (from input, network, or scripts)
    //        cym::CAnimationSystem::update() // update animations
    //        ?
    //      [update:physics]
    //        cym::CScene::query() -> CResult
    //        cym::CPhysicsResolver::resolve(CResult) -> psx lib
    //      [update:pre-render]
    //        cym::CTextureManager::update()  // dynamic textures (mirrors,screens...)
    //
    //    [render]
    //      [layer:game/main/background]
    //        CDeferredRenderer::render(CNodeScene)
    //          CScene::query(for_drawable_objects)
    //          for (object : objects)
    //            COpenglContext::draw({object}) -> draw to fbo
    //            
    //            ???CConsoleContext::draw({object}) -> draw to sprite=char buffer
    //        
    //        CRaycastRenderer::target(layer->target)
    //        CRaycastRenderer::render(CGlyphScene)
    //          for (x = 0; x < screen_width; x++)
    //            cast_ray_algo()
    //            for (y = 0; y < screen_width; y++)
    //              CConsoleContext::draw({char,x,y}) -> screen_buffer[y * height + x] = char
    //              COpenglContext::draw({?,x,y}) -> fbo?
    //              CWindowContext::draw({?,x,y}) -> image buffer?
    //      [layer:gui/game messages] // ("game over")
    //        CRenderer::draw(image);
    //      [layer:menu]
    //        ?
    //      [layer:console]
    //        ?
    //      [layer:debug(stats)]
    //        ?
    //      [present]
    //        engine->present()



### http://www.swiftless.com/terraintuts.html


### cym::CLayer
    // cym::CIntroLayer
    // cym::CLoadLayer
    // cym::CMenuLayer
    // cym::CMainLayer // CSceneLayer
    // cym::CDebugLayer

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

### engine #############################################################################################################
```cpp
// layer:scene/game
// layer:hud        //
// layer:menu       // 
// layer:load/intro
// layer:console
// layer:debug

// class CPanel : CWidget
// class CLayout : CWidget
// class CButton : CWidget
// class CViewport : CWidget
// class CLayer : CWidget
// class CSurface : CWidget
  // cym::CFramebuffer mFramebuffer
```
```cpp
// MODES
  // mode:loading
    // render intro screen
  // mode:playing
    // render (top) gui::CPanel => render each children => ...
```
```cpp
// SYSTEMS
  // fire
  // clouds
  // fog
  // animations
```
#### init
```cpp
// uix::CWindow() // create window (layout)
  // ...

// uix::COpenglContext // create context (opengl)
  // ...

// gui::CInterfaceManager::boot()
  // gui::CInterface(uix::CWindow)
    // EDITOR
    // gui::CPanel #main                                        // opengl object // contains all gui
      // gui::CBoxLayout::VERTICAL
        // gui::CPanel #menubar
          // gui::CMenu = FILE
            // gui::CMenuItem = OPEN
              // onClick => new gui::CFileDialog (gui::CPanel#content)
            // ...
          // ...
        // gui::CPanel #content
          // gui::CBoxLayout::HORIZONTAL
            // gui::CPanel = LEFTBAR        // tool bar
              // gui::CButton               // this could be inside a layout also
              // gui::CButton               
            // gui::CPanel[#viewport]
              // gui::CViewport             // where the scene is rendered
                // gui::CLayer = SCENE
                  // gui::CSurface
                // gui::CLayer = MENU       // viewport menus
                  // gui::CPanel = VIEWMENU // 
        // gui::CPanel #statusbar (or #infobar)
          // gui::CText
    // PLAYER
    // gui::CPanel
      // gui::CViewport
        // gui::CLayer = SCENE
          // 
        // gui::CLayer = HUD
        // gui::CLayer = MENU
        // gui::CLayer = INTRO
        // gui::CLayer = CONSOLE
        // gui::CLayer = DEBUG

// cym::CProcessManager::boot() // command/controller/task

// cym::CCodecManager::boot()

// cym::CPhysicsSystem::boot()
  // attach plugins
  // init force processor/logic // gravity

| | - EXEC cym::CRenderEngine::boot()
| | /// init render state
| | /// plugin renderers? // raycast, forward, deferred?
| | - INIT present pass (fbo)
| | | - CREATE color GL_RGBA32F + GL_RGBA + GL_FLOAT + BILINEAR + CLAMP_TO_EDGE
| | - INIT geometry pass (fbo)
| | | - CREATE depth   = GL_DEPTH_COMPONENT + GL_FLOAD + BILINEAR
| | | - CREATE color   = GL_RGB + GL_FLOAT + BILINEAR
| | | - CREATE normals = GL_RGB32F + GL_RGB + GL_FLOAT + BILINEAR
| | | - CREATE glow    = GL_R32I + GL_RED + GL_FLOAT = BILINEAR
| | | - CREATE motion  = GL_RG32F + GL_RG + GL_FLOAT = BILINEAR
| | - INIT occlusion pass (fbo)
| | | - CREATE color   = GL_R32F + GL_RED = GL_FLOAT + NEAREST + CLAMP_TO_EDGE

// cym::CShaderManager::boot()
  // compile shaders

// cym::CMaterialManager::boot()
// cym::CTextureManager::boot() 
// cym::CGeometryManager::boot()
// cym::CSceneManager::boot()
  // init scene (empty or file)
    // cym::CScene
      
  // load (virtual) camera // not bound to the scene
  // load (virtual) gizmo  // not bound to the scene
  // load (virtual) grid (scale,rotate,move)

// cym::CSystemManager::boot()
  // init all systems
  // particle system
  // 
```
#### loop
```cpp
- LOOP
| 
| - UPDATE
| | - EXEC cym::CInputManager::update()
| | /// pool for user input/events 
| | /// new cym::CCommand()
| | 
| | - EXEC gui::CInterfaceManager::update()
| |
| | - EXEC cym::CPhysicsSystem::update()
| | /// apply forces (gravity,wind)
| | /// apply acceleration, change velocities 
| | /// new cym::CCommand()
| | 
| | - EXEC cym::CCommandManager::update()
| | /// (from dialog)  command the opens scene file and merges w/ current (probably empty) one
| | /// (from dialog)  command that opens new model file and adds it to scene root (ASYNC) (starts as an empty model)
| | /// (from ai )     command move scene nodes
| | /// (from network) command move scene nodes
| | /// (from inputs)  command move scene nodes (node:scene OR node:joint)
| | ///// UPDATE node.position (or matrix)
| | ///// IF node.cell.AABB & node.AABB match
| | /////// no octree canges
| | ///// ELSE check w/ parent cell (and so on)
| | /////// update node's cell // node.cell = node.cell.parent 
| | ///// IF node exists root cell 
| | //////// (scene reset) add it to COctree::mDangling
| | /// (from button)  create box => (ASYNC) create model using glm::cube{} (model starts empty) 
| | ///// ...
| | /// update the state of the game
| | ///// refresh scene state
| | /////// update screen octree
| | ///////// IF octree.isDirty (has dangling)
| | /////////// octree.refresh/repartition
| | 
| | - EXEC cym::CCollisionResolver::resolve()
| | /// update state & positions of all scene objects 
|
|
| - RENDER|deferred
| | - FOR EACH cym::CWindow
| | | - EXEC gui::CInterfaceManager::render(cym::CWindow)
| | | | - EXEC gui::CPanel[#main]::render()
| | | | | - EXEC gui::CPanel[#menubar]::render()
| | | | | | - DRAW quad
| | | | | | - EXEC gui::CMenu[#file]::render()
| | | | | | | - DRAW quad
| | | | | | | - IF open
| | | | | | | | - EXEC gui::CMenuItem[#open]::render()
| | | | | | | | | - IF selected
| | | | | | | | | | - UNIFORM color red
| | | | | | | | | - DRAW quad
| | | | | | | | | - DRAW text
| | | | | | | | - EXEC gui::CMenuItem[#close]::render()
| | | | | | | | | - DRAW quad
| | | | | | | | | - DRAW text
| | | | | - EXEC gui::CPanel[#content]::render()
| | | | | | - EXEC gui::CPanel[#toolbar]::render()
| | | | | | - EXEC gui::CPanel[#viewport]::render()
| | | | | | | - EXEC gui::CViewport::render()
| | | | | | | | - EXEC gui::CLayer[#scene]::render()

| | | | | | | | | - EXEC cym::CRenderEngine::clear()
| | | | | | | | | /// shadow phase
| | | | | | | | | - QUERY scene : FIND lights WHERE ((light.position - camera.position) < 10)
| | | | | | | | | - FOR EACH light IN lights
| | | | | | | | | | - 
| | | | | | | | | 
| | | | | | | | | 

| | | | | | - EXEC gui::CPanel[#treeview]::render()
| | | | | - EXEC gui::CPanel[#statusbar]::render()

// render
  for each cym::CWindow // for each window w/ opengl context inside
  // gui::CInterfaceManager::render(cym::CWindow)
    // gui::CPanel::render()
      // ...
        // gui::CPanel[#menubar]::render()
          // gui::CMenu[#file]::render()
            // if OPEN
              // draw quad containing all gui::CMenuItem(s) quads
              // gui::CMenuItem::render()
                // draw quad
                  // if SELECTED
                    // color = red

      // gui::CPanel[#content]::render()
        // for each children ::render()

        // gui::CLayer::render() // SCENE
          // cym::CRenderEngine::clear()

          // SHADOW phase
            // for each light
              // set light render state
              // set FBO for shadow map
              // set camera = (light->camera) // for rendering  
              // entities = cym::CScene::query(camera->frustum) //  scene for entities w/ drawables components
              // for each entity
                // draw drawable

          // set camera = (virtual camera) // for rendering
          // entities = cym::CScene::query(camera->frustom) // for entities w/ drawables components

          // DRAW phase
            // for each entity
              // draw entity's drawable
                // if READY
                  // draw drawable

          // DEBUG phase
            // for each entity
              // if NOT READY
                // draw debug (spinner or bbox) at origin
              // draw entity's debugable
                // draw bbox (if selected)
                // draw icon (lightbulb,emitter,force...)
          
          // TOOL pase
            // draw grid
            // draw gizmo

          // post processing pass (bloom, ao, color...)
```
#### free 


























##### http://www.swiftless.com/terraintuts.html


##### https://code.visualstudio.com/docs/cpp/config-mingw
##### https://code.visualstudio.com/docs/cpp/CMake-linux