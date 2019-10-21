## C++ OpenGL API Game Engine

### API
###### VBO + IBO + VAO
```c++
GLfloat p[] = {-0.5,-0.5, +0.5,-0.5, +0.5,+0.5, -0.5,+0.5};  // vertex.positions
GLint   e[] = {0,1,2, 1,2,0};                                // indices(elements)

glo::CArray        a;                             // vao + vbo + ibo                              
glo::CVertexBuffer b(p, 4 * 2 * sizeof(GLfloat)); // vbo => ::glGenBuffers() + ::glBindBuffer(GL_ARRAY_BUFFER...) + ::glBufferData()
glo::CIndexBuffer  i(e, 6);                       // ibo => ::glGenBuffers() + ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER...) + ::glBufferData()
glo::CVertexLayout       l;                             // layout, stores how many (here) floats are there per vertex component

l.push({GL_FLOAT, 2, GL_FALSE}); // tell layout about the each vertex component (=2 floats) => adds to a list of elelemts
a.buffer(b,l);                    // add buffer + layout to VAO => does ::glEnableVertexAttribArray() + ::glVertexAttribPointer()

a.bind();  // bind vao => ::glBindVertexArray()
i.bind();  // bind ibo => ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER...)

::glDrawElements(GL_TRIANGLES,i.count(),GL_UNSIGNED_INT,GL_NULL); // execute draw call using ibo
```
###### Shader
```c++
glo::CShader s{"res/shaders/simple/color.glsl"};
s.bind();
s.uniform("u_vColor", .3f,.5f,.7f, 1.f);
s.bind(false);
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
- refactor: move loop logic into a `CGameLoop` class that has update & render listeners 
- use: `wglSwapIntervalEXT` in `CContext`
- update: move macros from `uix` to `sys` (sys should be everywhere)
- use: `::glDebugMessageCallback`
- question: should `GLCALL` + `::glCheckError` trigger a system event to the `uix::CContext`
- move: opengl code from `uix::CContext` to `glc::CContext : uix::CContext` // `uix` should stay abstract
- refactor: consider moving `glc`+`glo` into `ogl` and putting everything inside a namespace
- fix: need alternative for calling virtual methods from constructors
- fix: wglMakeCurrent() fail on app destroy // problem w/ the loop // close + destroy called before quit 
- restructure: move `CSufrface` + `CButton` (and panels) to `CEditWindow`
- new: `CWindowApplication` or `???` // application that is also a (main) window // can extend `CCanvas` (for game)
- use: get unforms & attributes using `glGetActiveAttrib` && `glGetActiveUniform`
- replace(use): custom types (typedef uint) instead of opengl's GLxxx types
- oop: !!! really need an empty default constructor declared in the header
- attach `CContext` to window(s) // by ref?!
- create engine (using context)
  - add viewports (windows + cameras) to engine // new `CViewport` = `CWindow` + `CCamera`
  
- precision: `#ifdef OGL_DOUBLE_PRECISION` -> `typrdef double real` #else `typedef float real`

- `glx` draw something // start the ogl framework
  - engine picks the context
  - move `CContext` to ogl (since it uses only opengl) // `uix::ogl::CContext` // `uix::COGLContext` extends `ogl::CContext`
    - `CSurface` + `CCanvas` takes `CContext`(or ref) not SConfig

- timer (proper timer object w/ start & elapsed)

- move window create logic from `CWindow` to `CFrame` (first concrete child) and others
- `SConfig`: replace window hints w/ config
- `SState`: window & application states for persistance
- fix: leak: all ::GetDC() MUST have a ::ReleaseDC()
- fix: move free() from base class to superclass // last free doesn't trigger

- namespaces: sys & com(replace fix)

- loop: engine onUpdate & onRender

- object: add custom ids // if try to use same id crash

- enum class: find an alternative or implement hintbag

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
- logger: should get instance on app instance / solve the unique_ptr init problemcccccclctidrvbijekchniftkvffbvndtrivvlfjtduv
- registries should init only on app init | use CSingleton & CPointer

- style (window) switcher
- styles: revisited (application) integrate UIX_STYLE // ifndef use win32 else use UIX_STYLE
- window: alpha/transparency usin' layered windows
- widget: widgets don't init until added to toplevel(popup) windows 

- finish: mouse click events // pair events (mouse click, key press/tab) 
- finish: window events
- finish: painter
- finish: button

- context: opengl stereo + debug flags

- most pointers should be wrapped by a smart pointer object

- surface != panel // need something above (or just use widget) // panel for controls // surface for opengl
- throw exception on windows create failed + loop + try + fatal or warning // where to use them

- app: 2 panels: 1x canvas +1x buttons (like spawn a sphere)

- sys.cpp | include all lib .cpp files inside a sys.cpp file to build a single .obj file 
- `std::array` vs `boost::static_vector` (dynamic fixed array)  


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
- code
  - `CMeshBuilder`
    - `CMD5MeshBuilder`
    - `CSphereMeshBuilder::build(CSphereMeshBuilder::EStrategy)` -> `CMesh` 
      - `EStrategy::ICOSPHERE`                   // uses icosahedron to build a sphere
      - `EStrategy::CUBESPHERE`                  // uses a cube to build a sphere 
      - `EStrategy::UVSPHERE`  (this looks hard)
  - `CCubeMeshBuilder`
  - `CPyramidMeshBuilder::build(int nSides)`     // now many edges the base has // can be used to build a cone

  - `CTextureBuilder`
    - `CSimplexTextureBuilder`
    - `CDDSTextureBuilder` 
    - `CTGATextureBuilder` 
    - `CPNGTextureBuilder` 
  
  - `CAnimationBuilder`
    - `CMD5AnimationBuilder`
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
- opengl
  - unbinding might not be necesarry, make it do nothing in non-debug mode
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
###### `glo` # graphic library objects # camera, mesh, material
###### `net` # networking library # tcp, udp, sockets, http
###### `uix` # user interface extended # wrappers for windows, controls, buttons


### App::edit|make
- structure
    - splash window
      - build/load shaders
      - present app
      - preload next (edit) window
    - edit (main) window
        - layouts: [4xViewports] | [2xLeft + 1xRight] | [1xRight + 2xLeft] | [1xTop + 1xBottom] | [1xViewport]
        - projection: [perspective] | [orthographic] 
        - init: 
            - create opengl context
            - open game.xml & scene.xml 
            - setup virtual cameras (views) (not saved w/ the scene)
            - send asses to be loaded in the background 
        - idle: draw scene/objects - once a new one is avaiable added to the draw call
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
