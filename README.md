## C++ OpenGL API Game Engine



### 2021-08-07 #########################################################################################################

#### EDIT
```text
INIT
| EXEC load windows/layout
| | LOAD main window
|   | LOAD layout
|     | LOAD toolbar (top)   (buttons)
|     | LOAD toolbar (left)  (buttons)
|     | LOAD sidebar (right) (scene tree)
| 
| EXEC load context (to be shared w/ all surfaces)
| | ?
| 
| EXEC load viewports & layers
| | LOAD edit viewport
| | LOAD show viewport (inactive)
|   | LOAD debug layer
|   | LOAD draw layer
| | LOAD test/play viewport
|   | EXEC onInit (=pause all other viewports)
|   | LOAD debug layer
|   | LOAD gui layer
|   | LOAD info/error/message layer
|   | LOAD console layer
|   | LOAD draw layer
|   | EXEC onExit (=un-pause everything else) 
|
| LOAD (all) shaders // all shader combinations (animation,wireframe,lighting model,light/flat)
| | ?
|
| LOAD (all built-in) shapes (cube,frustum,sphere?), axor (3 perpedicular axis + 3 cones/pyramids)
| | ?
|  
| LOAD fonts/text manager // fonts and their textures and sizes
|  
| LOAD grid, gizmo, normal-axor (3axis=3lines+3cones)
| | ?
|
```
```text
LOOP while true // forward render
| // here: make/poll, update...
| 
| FOREACH viewport
| | EXEC render main layer
| | | EXEC shadow pass
| | |     ...
| | EXEC render gui layer
| | | ? 
| | EXEC render debug layer
| | | ?
|   
| EXEC render main/edit/game viewport
| | MAKE viewport + context active
| | 
| | EXEC render main layer
| | | QUERY (drawables = FIND drawble IN scene WHERE aabb in camera.frustum)  
| | |
| | | EXEC shadow pass
| | | | FOREACH:light in lights
| | | |  
| | | |   IF light.isShadowCaster != true
| | | |     skip!
| | | |  
| | | |   FOREACH layer (light layer) 
| | | |     
| | | |     BIND shader (spot,point,direct light OR 1 for all) 
| | | |     
| | | |     BIND fbo shadow
| | | |     
| | | |     BIND light 
| | | |       UNIFORM V = glm::lookat(light.position, light.direction, glm::Y) // for omni use GL_TEXTURE_CUBE_MAP_POSITIVE_? 
| | | |       UNIFORM M = light.M
| | | |      
| | | |     FOREACH model/drawable in models
| | | |       
| | | |       IF model.isShadowCaster != true
| | | |         skip!
| | | |      
| | | |       BIND: model/drawable
| | | |         UNIFORM M = mode.matrix
| | | |         
| | | |       DRAW model // output color = depth
| | | 
| | | EXEC draw pass
| | | | BIND fbo 0
| | | |   clear color & depth
| | | | 
| | | | BIND render state // viewport, depth, culling
| | | |
| | | | FOREACH model/drawable in models
| | | |   BIND shader // don't rebind (if already bond)
| | | | 
| | | |   IF model.drawmode != FULLMODE or WIREFULL
| | | |     skip!
| | | |   
| | | |   BIND shadow // GL_TEXTURE1
| | | |   
| | | |   FOREACH light in lights
| | | |     BIND light (to shader)
| | | |       UNIFORM light.position
| | | |       UNIFORM light.color
| | | |       UNIFORM light.direction
| | | |       UNIFORM light.intesity
| | | |     
| | | |   BIND:camera (to shader)
| | | |     UNIFORM camera.position
| | | |     UNIFORM camera.V = V
| | | |     UNIFORM camera.P = V
| | | |     
| | | |   BIND model/drawable
| | | |     UNIFORM model.matrix = M
| | | |     
| | | |   FOREACH mesh in model->meshes
| | | |     FOREACH joint in joints
| | | |       BIND joint (matrix, u_mB[x]) 
| | | |   
| | | |     FOREACH material
| | | |       BIND material (to shader)
| | | |         UNIFORM material.options
| | | |         FOREACH channel
| | | |           UNIFORM color // if needed
| | | |           UNIFORM texture SAMPLER/SLOT (to shader) // activate texture slot (get info from shader object)
| | | |         
| | | |     BIND:mesh (to shader)
| | | |       UNIFORM:mesh.variables (to shader) // like variable positions (for on a cube, if u'r using only 1 cube ibo)
| | | |        
| | | |     BIND vao
| | | |     BIND vbo/ibo
| | | |     DRAW call // draw mesh
| | |
| | | EXEC debug pass: wireframe
| | | | FOREACH model/drawable
| | | |   BIND shader
| | | |   
| | | |   IF editor.settings != WIREMODE or WIREFULL
| | | |   OR model.drawmode != WIREMODE or WIREFULL
| | | |     skip!
| | | |   
| | | |   FOREACH joint in joints // needs to follow animation (or use transform feedback?!)
| | | |     BIND joint (matrix, u_mB[x])
| | | |       UNIFORM B (joint ...)
| | | |   
| | | |   BIND camera (to shader)
| | | |     UNIFORM V (camera.V)
| | | |     UNIFORM pos (camera.position)
| | | |     UNIFORM P (camera.P)
| | | |     
| | | |   draw model
| | | |     FOREACH mesh in model->meshes
| | | |       
| | | |       FOREACH joint in joints
| | | |         BIND joint (matrix, u_mB[x])
| | | |         
| | | |       BIND vao
| | | |       BIND ibo
| | | |       DRAW call // draw mesh's vbo/ibo
| | | 
| | | EXEC:debug pass: normals 
| | | | FOREACH model/drawable
| | | |   bind shader
| | | |   
| | | |   IF editor.settings != SHOWNORMALS
| | | |   OR model.drawmode != SHOWNORMALS
| | | |     skip;
| | | | 
| | | |   bind camera (to shader)
| | | |     
| | | |   draw axor
| | | |     bind vao
| | | |     bind vbo/ibo
| | | |     draw call
| | | 
| | | EXEC:debug pass: bbox
| | | | FOREACH drawable
| | | |   bind shader
| | | |   
| | | |   if model.selected != true
| | | |     skip!
| | | |   
| | | |   draw (line) cuboid // only lines
| | | |     bind mesh (to shader)
| | | |       bind mesh uniforms (to shader) // cuboid
| | | |   draw (point) cuboid // only points
| | | |     ...
| | 
| | 
| | EXEC:draw gui layer
| | |  draw gui elements // items, hit marks, screen-space effects(rain,blood...)?!
| | |  
| | | // for editor, draw gui version of gizmo/axor, that matches orientation on screen
| | 
| | 
| | EXEC:draw menu/pause layer
| |   // pause the game + keep the last (draw layer) fbo  
| |   IF app.isPaused == true
| |     draw menu // 3d (model-space) OR 2d(screen-space) 
| |     
| |     FOREACH message
| |       draw msg box // in screen space 
| | \EXEC
| | 
| | 
| | EXEC:draw console
| |   IF app.showConsole == true
| |     draw console // in screen-space
| | \EXEC
| | 
| | 
| | EXEC:draw debug layer
| |   draw debug info (fps,gpu,cpu,temp) box // in screen space 
| | \EXEC
|  
| 
| SWAP:fbo
```  
  



------------------------------------------------------------------------------------------------------------------------
### PAST ###############################################################################################################

#### TODO
- layers
- viewports | `CViewport` = `CCamera` + ???

#### Notes

#######
- fix: dds texture flipped
- fix: texture setWrapping + setFiltering + blending
- use std::string_view instead of allocation a new std::string
- glMapBufferRange is faster
- parallel loops std::for_each(std::execution:par_unseq, std::vector::begin(), std::vector::end())
- new: sys info object // like getting the number threads/cores 
- enum class: find an alternative or implement HintBag
#######
- material techniques: lambert(emission+ambient+diffuse+mIOR), phong(emission+ambient+diffuse+specular+transparency+shininess+mIOR), blinn...
#######
- instancing: MaterialInstance = wrapper of around the material, that overrides materials



#### WINDOWS

                                                +-------------------------------------+
                                                |                                     |
                                                |                                     |
                                                |                                     |
                                                |                                     |
                                                |                splash               |
                                                |                                     |
                                                |                                     |
                                                |                                     |
                                                |                                   o |
                                                +-------------------------------------+

    +----------------------------------------------------+                  +-------------------------------------------------------+
    | [O] | File Edit View | project name        | _ # X |                  |                                                       |
    |-----+--------------------------------------+-------|                  |                                                       |
    | [a] : [b] : [c] : [d] : [e]         [Tools] [Play] |                  |                                                       |
    |-----+------------------------+---------------------|                  |                                                       |
    | [1] | view 1: 3d |           | world |             |                  |                                                       |
    |     +------------+           +-------+             |                  |                                                       |
    | [2] |                        | + root              |                  |                                                       |
    |     |                        |   + scene:node 01   |                  |                                                       |
    |     |                        |   + scene:node 02   |                  |                        game window                    |
    |     |                        | [ - SELECTED node ] |                  |                                                       |
    |     |                        |     + sub-element   |                  |                                                       |
    |     |                        |   [ - sub-element ] |                  |                                                       |
    |     |                        |                     |                  |                                                       |
    |     |            +--------------------------------------------+       |                                                       |
    |-----+------------| [] title bar: PlayWindow             _ # X |       |                                                       |
    | (status bar)     |--------------------------------------------|       |                                                       |
    +------------------|                                            |       +-------------------------------------------------------+
                       |                                            |
         +----------------------+                                   |
         | [] Load          _ X |                                   |
         |----------------------|                                   |
         |+--------------------+|                                   |
         || dasdasd.dae        ||                                   |
         || dasdasd.fxb        ||                                   |
         |+--------------------+|                                   |
         |             [ Load ] |                                   |
         +----------------------+                                   |
                       |                                            |
                       +--------------------------------------------+

- EditWindow : Window/Toplevel
  - TitleBar : ?
  - Menu : Menu
  - LeftSidebar : Window/?
  - Navigator   : Window/Tree
  - Workspace : Window + Layout (4 grid) or (2 horizontal box) or (default: 1 windwo)
    - Viewport : Window + Camera
  
#### GAME: game.xml

```xml
<?xml version="1.0" encoding="utf-8"?>
<game>
  <level>
    <scene source="path/scene.xml" />
    <scene>
      <model source=""/>
      <effect/>
      <trigger/>
      <light/>
      <camera/>
      <force/>
    </scene>
  </level>
</game>
```


#### STRUCTURE

- loop
```c++
for (CViewport* pViewport : get_viewports())
  for (CGeometry* pGeometry : get_models())
    pGeometry->draw();
```

- cameras:
```c++
class CCamera;
class CVirtualCamera : CCamera; // not a node in the scene
class CSceneCamera   : CCamera; // camera node in the scene
```

- rendering
```c++
CQuery query = CQuery::from(CFrustum);
std::vector<CNode> pNodes = CScene::query(query);

```


    // model  <- entity <- drawable
    // effect <- entity <- drawable

    // loop
      // update
      // render visual    | ngn::CRenderer
      // render sound     | snd::CRenderer
      // render feedback  | ffb::CRenderer


##### Layers

    - DEBUG layer (debug info, fps, cpu...)
    - PANIC layer (error, message boxes)
    - CONSOLE layer (console terminal)
    - MENU (main) layer 
    
    - PAUSE (menu) layer
    - GUI (/hud) layer
    - GAME layer 


##### INIT

    - INIT
    |
    | - INIT (deferred) renderer
    | | - INIT preset pass (fbo)
    | | | - CREATE color GL_RGBA32F + GL_RGBA + GL_FLOAT + BILINEAR + CLAMP_TO_EDGE
    | | - INIT geometry pass (fbo)
    | | | - CREATE setDepth   GL_DEPTH_COMPONENT + GL_FLOAT + BILINEAR
    | | | - CREATE color   GL_RGB + GL_FLOAT + BILINEAR
    | | | - CREATE normals GL_RGB32F + GL_RGB + GL_FLOAT + BILINEAR
    | | | - CREATE glow    GL_R32I + GL_RED + GL_INT + BILINEAR
    | | | - CREATE motion  GL_RG32F + GL_RG + GL_FLOAT + BILINEAR
    | | - INIT occlussion pass (fbo)
    | | | - CREATE color   GL_R32F + GL_RED + GL_FLOAT + NEAREST + CLAMP_TO_EDGE
    
    
##### LOOP

    - LOOP
    |  
    | - UPDATE
    | | - FOR EACH entity
    | | | - UPDATE entity
    |   
    |   
    | - RENDER:deferred
    | | - shadow pass
    | | | - QUERY scene : FIND lights WHERE |light.position - camera.position| < 10 
    | | | - FOR EACH light : lights
    | | | | - IF light CAN (make) shadow
    | | | | | - CREATE (shadow) framebuffer
    | | | | | 
    | | | | | - FOR EACH layer (6 layers for POINT light, 1 layer for the rest)
    | | | | | | - BIND (shadow) framebuffer (layer) (cubemap=6 for omni/point lights)
    | | | | | | - DISABLE read/write color
    | | | | | | - CLEAR  color & setDepth
    | | | | | |  
    | | | | | | - frustum = CREATE from light
    | | | | | | - QUERY scene : FIND drawables WHERE drawable IN frustum
    | | | | | | - FOR EACH drawable
    | | | | | | | - IF drawable CAN (cast) shadow
    | | | | | | | | - BIND (shadow) shader
    | | | | | | | | 
    | | | | | | | | - IF drawable|shader IS tessellated
    | | | | | | | | | - GL_PATCHES 
    | | | | | | | | 
    | | | | | | | | - UNIFORM M = drawable.matrix
    | | | | | | | | - UNIFORM V = light.matrix 
    | | | | | | | | - UNIFORM P = perspective_matrix (60fov)
    | | | | | | | | 
    | | | | | | | | - FOR EACH joint
    | | | | | | | | | - UNIFORM joint.matrix
    | | | | | | | | 
    | | | | | | | | - DRAW drawable
    | | | | | | | | | - BIND vao
    | | | | | | | | | - BIND ibo
    | | | | | - LINK shadow TO light (=shadow cast by that light)
    | | 
    | | 
    | | - geometry pass
    | | | - SET flags (cull face back, setDepth)
    | | | - BIND (geometry) framebuffer (setDepth + color + normals + motion)
    | | | 
    | | | - frustum = CREATE from camera
    | | | - QUERY scene : FIND drawables WHERE drawable IN frustum ORDER front2back(opaque) GROUP BY shader, model
    | | | # render opaque first, then transparent
    | | | - QUERY scene : FIND drawables WHERE drawable IN frustum ORDER back2front(transparent)
    | | | - FOR EACH drawable : drawables
    | | | | - BIND (geometry) shader: DEFERRED + GEOMETRY + SINGLE + MOTION(blur) + PARALLAX
    | | | |
    | | | | - IF drawable IS tessellated
    | | | | | - GL_PATCHES
    | | | |
    | | | | - UNIFORM (current)  M drawable.matrix
    | | | | - UNIFORM (previous) M drawable.matrix // for motion blur
    | | | | 
    | | | | - UNIFORM V = camera.view
    | | | | - UNIFORM camera.position 
    | | | | - UNIFORM P camera.projection
    | | | |  
    | | | | - FOR EACH joint
    | | | | | - UNIFORM B = joint.matrix
    | | | | 
    | | | | - FOR EACH material (=bind material)
    | | | | | - UNIFORM material.options
    | | | | | - FOR EACH channel
    | | | | | | - UNIFORM texture
    | | | | | | - UNIFORM color
    | | | | | | - UNIFORM level
    | | | | 
    | | | | - DRAW drawable
    | | | | | - BIND vao
    | | | | | - BIND ibo
    | | 
    | | 
    | | - occlussion pass
    | | | - BIND (occlusion) framebuffer FOR write
    | | | - BIND (occlusion) shader
    | | | 
    | | | - UNIFORM V = camera.vew 
    | | | - UNIFORM P = camera.projection 
    | | |  
    | | | - UNIFORM kernel (=vec3 (vector) array = )
    | | | - UNIFORM noise texture
    | | | 
    | | | - BIND/UNIFORM geometry.depth   framebuffer AS setDepth texture  
    | | | - BIND/UNIFORM geometry.normals framebuffer AS normals texture  
    | | | 
    | | | - DRAW fullscreen QUAD
    | | | 
    | | | - BIND (occlusion) framebuffer FOR write & read
    | | | - BIND (blur) shader
    | | | - COPY/CLONE (occlussion) FRAMEBUFFER color attachement
    | | | - UNIFORM clone
    | | | 
    | | | - DRAW fullscreen QUAD
    | | 
    | | 
    | | - lighting pass
    | | | - (UN)SET flags (setDepth, stencil, blend, cull_face, back)
    | | | 
    | | | - BIND (output=0) framebuffer 
    | | | 
    | | | - BIND (lighting) shader
    | | | 
    | | | - BIND (framebuffer) geometry.depth   AS setDepth texture
    | | | - BIND (framebuffer) geometry.normals AS normals texture
    | | | - BIND (framebuffer) geometry.diffuse AS diffuse texture
    | | | 
    | | | - BIND (framebuffer) occlussion.color AS occlussion texture 
    | | | 
    | | | - FOR EACH light : lights
    | | | | - FOR EACH layer : light.shadow.layers
    | | | | | - UNIFORM light.color
    | | | | | - UNIFORM light.position
    | | | | | - UNIFORM light.ambient
    | | | | | - UNIFORM light.diffuse
    | | | | | - UNIFORM light.coefficients (k0, k1, k2)  
    | | |  
    | | | - DRAW fullscreen quad
    | | 
    | | 
    | | - motion pass
    | | | - BIND (output=0) framebuffer FOR read & write
    | | | - BIND (motion) shader : MOTION
    | | | - UNIFORM (framebuffer) output.color AS color (GL_TEXTURE0)
    | | | - UNIFORM (framebuffer) geometry.motion AS motion (GL_TEXTURE1)
    | | | - DRAW fullscreen quad 
    | | 
    | | 
    | | - debug pass
    | | | - BIND (output) framebuffer 
    | | | 
    | | | - FOR EACH mode ["normals", "icons", "wireframe"]
    | | | | - SWITCH mode
    | | | | | - CASE normals
    | | | | | | - BIND (debug.normals) shader
    | | | | | |
    | | | | | | - UNIFORM V = camera.view
    | | | | | | - UNIFORM P = camera.projection
    | | | | | |
    | | | | | | - FOR EACH entity
    | | | | | | | - UNIFORM M = entity.matrix
    | | | | | | | - DRAW normals
    | | | | | | 
    | | | | | - CASE icons
    | | | | | | - BIND shader
    | | | | | | - FOR EACH entity
    | | | | | | | - DRAW icon
    | | | | | | 
    | | | | | - CASE wireframe
    | | | | | | - BIND (debug) shader
    | | | | | | - FOR EACH entity
    | | | | | | | - DRAW icon
    | | 
    | | 
    | | - final pass
    | | | - DISABLE setDepth & stencil
    | | | - SET final opengl flags
    | | | - BIND (output=0) framebuffer
    | | | - SET viewport (setRatio,setHeight of output)
    | | | - UNIFORM (framebuffer) output.color AS texture GL_TEXTURE1
    | | | - DRAW fullscreen quad
      
    
    

---    
    
    
    
    
    | - RENDER:forward
    | | - final pass
    | | | - BIND framebuffer 0
    | | | | - CLEAR color & setDepth 
    | | | - FOR EACH drawable
    | | | | - BIND (render) shader
    | | | | 
    | | | | - BIND shadow (GL_TEXTURE1)
    | | | | 
    | | | | - FOR EACH material
    | | | | | - UNIFORM material.options
    | | | | | - FOR EACH channel
    | | | | | | - UNIFORM texture
    | | | | | | - UNIFORM color
    | | | | 
    | | | | - UNIFORM drawable.matrix (M)
    | | | | - UNIFORM camera
    | | | | | - UNIFORM camera.matrix (V)
    | | | | | - UNIFORM camera.position 
    | | | | | - UNIFORM camera.projection (P)
    | | | | 
    | | | | - FOR EACH joint
    | | | | | - UNIFORM joint.matrix
    | | | | 
    | | | | - FOR EACH light
    | | | | | - UNIFORM light 
    | | | | | | - UNIFORM light.direction
    | | | | | | - UNIFORM light.color
    | | | | | | - UNIFORM light.ambient_intensity
    | | | | | | - UNIFORM light.diffuse_intensity
    | | | | 
    | | | | - IF bWireframe
    | | | | | - UNIFORM bWireframe
    | | | | 
    | | | | - BIND vao
    | | | | - BIND ibo
    | | | | - DRAW drawable
    | | | 
    | | | - IF bShowLights
    | | | | - FOR EACH light
    | | | | | - DRAW light icon
    
    
------------------------------------------------------------------------------------------------------------------------
### OLDER #############################################################################################################

###### VBO + IBO + VAO
```c++
GLfloat p[] = {-0.5,-0.5, +0.5,-0.5, +0.5,+0.5, -0.5,+0.5};  // vertex.positions
GLint   e[] = {0,1,2, 1,2,0};                                // getIndices(elements)

cym::CVertexArray  a;                                     // vao + vbo + ibo                              
cym::CVertexBuffer b(p, 4 * 2, cym::CDataBuffer::VERTEX); // vbo => ::glGenBuffers() + ::glBindBuffer(GL_ARRAY_BUFFER...) + ::glBufferData()
cym::CIndexBuffer  i(e, 2 * 3, cym::CDataBuffer::INDEX);  // ibo => ::glGenBuffers() + ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER...) + ::glBufferData()
cym::CVertexLayout l;                                     // getLayout, stores how many (here) floats are there per vertex component

l.push({GL_FLOAT, 2, GL_FALSE}); // tell getLayout about the each vertex component (=2 floats) => adds to a list of elelemts
a.buffer(b,l);                   // add buffer + getLayout to VAO => does ::glEnableVertexAttribArray() + ::glVertexAttribPointer()

a.bind();  // bind vao => ::glBindVertexArray()
i.bind();  // bind ibo => ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER...)

::glDrawElements(GL_TRIANGLES,i.count(),GL_UNSIGNED_INT,GL_NULL); // execute draw call using ibo
```
###### Shader
```c++
cym::CShader s{"res/shaders/simple/color.csl"}; // chimera shader language
s.bind(0);                                      // slot 0
s.uniform("u_vColor", .3f,.5f,.7f, 1.f);
s.bind(false);
```
###### Texture
```c++
cym::CTextureManager* m = cym::CTextureManager::getSingleton();
cym::CTexture*        t = m->init(sys::CFile("res/textures/paint.dds"));

t.bind(0); /* OR */ s.sampler(t); // shader: set sampler = bind + activate + uniform
```

### Research
- `Game Programming Patterns` (by Robert Nystrom)
- `Game Coding Complete`
- `Game Engine Architecture` (by Jason Gregory)
- `enginuity` (gamedev.new)
- `https://github.com/SFML/SFML/wiki/Tutorial:-Basic-Game-Engine`
- `http://www.stuartmathews.com/index.php/gaming/938-a-simple-game-engine-architecture`
- `https://youtu.be/L19dBX53M5M` (bennybox)
- `https://gamasutra.com/blogs/MichaelKissner/20151027/257369/Writing_a_Game_Engine_from_Scratch__Part_1_Messaging.php`

### Needed

- new: `CWindowApplication` or `???` // application that is also a (main) window // can extend `CCanvas` (for game)
  - move: `CModule` inside `CApplication`
  - or refactor `uix::CApplication` into a toplevel window | `template<typename T=CWindow> CApplication`
- refactor: throw exception on `delete` `CWindow*` only the `CWindow::CRegistry` is allowed to
- refactor: `CPopup` to replace `CToplevel` | only close app if `CPopup` has no parent
- fix: need alternative for calling virtual methods from constructors
  - refactor: find a replacement `::init()` and `::free()`
- refactor: consider moving `glc`+`ogl` into `ogl` and putting everything inside a namespace 
- update: move macros from `uix` to `sys` (sys should be everywhere)
- use: `CGameLoop` to send update + render + make events to `CCore` and its sub-systems 
- use: `::glDebugMessageCallback`
- question: should `GLCALL` + `::glCheckError` trigger a system event to the `uix::CContext`
- move: opengl code from `uix::CContext` to `ogl::CContext : uix::CContext` // `uix` should stay abstract
- restructure: move `CSufrface` + `CButton` (and panels) to `CEditWindow`
- use: get unforms & attributes using `glGetActiveAttrib` && `glGetActiveUniform`
- .ext to lowercase for `cym::CCodec`s 
- replace(use): custom types (typedef uint) instead of opengl's GLxxx types
- attach `CContext` to window(s) // by ref?!
- opening files shouln't crash (through exception) the app, just show an error
- make engine (using context)
  - add viewports (windows + cameras) to engine // new `CViewport` = `CWindow` + `CCamera`
  

 

- `glx` draw something // start the ogl framework
  - engine picks the context
  - move `CContext` to ogl (since it uses only opengl) // `uix::cym::CContext` // `uix::COGLContext` extends `cym::CContext`
    - `CSurface` + `CCanvas` takes `CContext`(or ref) not SConfig

- timer (proper timer object w/ start & elapsed)

- move window make logic from `CWindow` to `CFrame` (first concrete attach) and others
- `SConfig`: replace window hints w/ config
- `SState`: window & application states for persistance
- fix: leak: all ::GetDC() MUST have a ::ReleaseDC()
- fix: move free() from base class to superclass // last free doesn't trigger


- loop: engine onUpdate & onRender

- object: add custom ids // if try to use same id crash



- listener/events: make CListener::mHandlers static (common for all intances)

- fullscreen: gaming (DEVMODE)
- custom theme - replace titlebar (icon+menubar+title+sysmenu)
- menus
- multithreading (::CreateProcess & pthreads)
- on resize/maximized restore canvas/surface'context (render area)
- handle ::WinMain + CApplication + CConsole + nCmdShow
- ::AnimateWindow()
- sys: os + fs + timer 
- logger: custom manipulators + multiple strategies (+file) + loggin w/ defines & macros
- logger: make CLogger::dbg/nfo/wrn/err reference to CLogger not ELevel or ELevel into a class
- logger: should get instance on app getSingleton / solve the unique_ptr init problem
- registries should init only on app init | use CSingleton & CPointer

- style (window) switcher
- styles: revisited (application) integrate UIX_STYLE // ifndef use win32 else use UIX_STYLE
- window: alpha/transparency usin' layered windows
- widget: widgets don't init until added to toplevel(popup) windows 

- update `uix::CWindow` system to use `PWindow = sys::CPointer<uix::CWindow>` like in ogl

- finish: mouse click events // pair events (mouse click, key press/tab) 
- finish: window events
- finish: painter
- finish: button

- context: opengl stereo + debug flags

- `uix` most pointers should be wrapped by a smart pointer object

- surface != panel // need something above (or just use widget) // panel for controls // surface for opengl
- throw exception on windows make failed + loop + try + fatal or warning // where to use them

- app: 2 panels: 1x canvas +1x buttons (like spawn a sphere)

- sys.cpp | include all lib .cpp files inside a sys.cpp file to build a single .obj file 
- `std::array` vs `boost::static_vector` (dynamic fixed array)
- refactor: find an alternative for `std::function` in `uix::CGameLoop`  
  - need a `sys::CFunction` = `[args...](){ }` that can take whatever comptures A need

### Architecture
##### `Game` (app)
##### `Game Engine`
##### `Graphic Engine`
##### `Graphic Framework`
##### `...`

### Engine
- needs opengl context
- needs build engine - pre-set up stuff (that may change later)
- render: // draws using draw calls (mesh + texture info)
  - for all objects/drawables
    - add draw call (w/ all necessary info)
  - render scene (draw calls/what camera sees)
```
                 +-----+
                 |Logic|
                 +-----+
                    ↓
               +---------+
               |Messenger|              // routes messages to engine systems/components
               +---------+
       ↓        ↓       ↓         ↓
    +-----+ +------+ +-----+ +-----+ 
    |Input| |Render| |Scene| |Audio| GUI AI 
    +-----+ +------+ +-----+ +-----+
       ↓        ↓       ↓       ↓
               +---------+
               |Framework|
               +---------+
        ↓       ↓       ↓       ↓
    +------+ +-----+ +-----+ +-----+
    |Render| |Input| |Sound| |Utils|
    +------+ +-----+ +-----+ +-----+
```
- messaging
  - messenger queue: too many messages this frame? queue them for the next one | control game fps
  - messenger handle messages w/ priority: 0 = now | 10+ = later
- memory:
  - fragmentation?!
  - use cpu L* cache levels
  - allocator // stack-based vs pool-based vs (multi)FRAME-based
    - frame-based: gets reset on each(or nth) frame
  - https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
  - https://medium.com/@mateusgondimlima/designing-and-implementing-a-pool-allocator-data-structure-for-memory-management-in-games-c78ed0902b69
- opengl
  - unbinding might not be necesarry, make it do nothing in non-debug mode
  - refactor: replace `::glBufferData + GL_STATIC_DRAW` with `::glBufferStorage`
- shaders
  - shader fragments
  - embeded shaders into clases that know about attributes + uniforms + ...
  - exception if the shader/program/pipeline fails to compile 
  - get unforms & attributes using `::glGetActiveAttrib` && `::glGetActiveUniform`
  - parse shader
    - have custom logic that reads tags like `#include` to extend shader system
    - use `#include file.xxx` to add functionality to the shader // this needs to be parsed by the engine
- gui|hud
  - see https://github.com/ocornut/imgui

### Physics
- bodies
  - rigid body   // w/ physics // w/ gravity (or other forces) // mass & weight(mass & gravity acc)
  - dynamic body // kinematic/animated // can be moved // no default physics // needs own physics rules 
  - static body  // doesnt move + other bodies can interact w/ it // no gravity (force) interaction
  - vehicul body
  - soft body 
- collision
  - polygon
  - shape
- material // physics material
  - friction
  - rough
  - bounce
  - absorb

### Framework
###### `sys` # system/core framework # io, error, string, files
###### `alc` # audio library core # sfx(effect) + music(track) + voice
###### `glc` # graphic library core # opengl
###### `glm` # graphic library math # g-trunc glm or...
###### `glw` # graphic library wrappers # buffer, shader, pipeline
###### `gls` # graphic library shapes # circle, sphere
###### `ogl` # graphic library objects # camera, mesh, material
###### `net` # networking library # tcp, udp, sockets, http
###### `uix` # user interface extended # wrappers for windows, controls, buttons

### App::edit|make
- structure
    - splash window
      - build/init shaders
      - present app
      - preload next (edit) window
    - edit (main) window
        - layouts: [4xViewports] | [2xLeft + 1xRight] | [1xRight + 2xLeft] | [1xTop + 1xBottom] | [1xViewport]
        - projection: [perspective] | [orthographic] 
        - init: 
            - make opengl context
            - open game.xml & scene.xml 
            - setup virtual cameras (views) (not saved w/ the scene)
            - send asses to be loaded in the background 
        - tick: draw scene/objects - once a new one is avaiable added to the draw call
- features:
    - play mode: opens a canvas w/ shared context that plays the game
```
    +----------------------------------------------------+
    | [O] | File Edit View | project name        | _ # X |
    |-----+--------------------------------------+-------|
    | [a] : [b] : [c] : [d] : [e]         [Tools] [Play] |
    |-----+------------------------+---------------------|
    | [1] | view 1: 3d |           | world |             |
    |     +------------+           +-------+             |
    | [2] |                        | + root              |
    |     |                        |   + scene:node 01   |
    |     |                        |   + scene:node 02   |
    |     |                        | [ - SELECTED node ] |
    |     |                        |     + sub-element   |
    |     |                        |   [ - sub-element ] |
    |     |                        |                     |
    |     |                        |                     |
    |-----+------------------------+---------------------|
    |                                                 [] |
    +----------------------------------------------------+
```

### App::play|game
- structure
    - play (main) window
        - fullscreen
