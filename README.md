## C++ OpenGL API Game Engine

##### Research
- `Game Programming Patterns` (by Robert Nystrom)
- `Game Coding Complete`
- `Game Engine Architecture` (by Jason Gregory)
- `enginuity` (gamedev.new)
- `https://github.com/SFML/SFML/wiki/Tutorial:-Basic-Game-Engine`
- `http://www.stuartmathews.com/index.php/gaming/938-a-simple-game-engine-architecture`
- `https://youtu.be/L19dBX53M5M` (bennybox)
- `https://gamasutra.com/blogs/MichaelKissner/20151027/257369/Writing_a_Game_Engine_from_Scratch__Part_1_Messaging.php`


##### Needed
- restructure: gl* into ONE unit/folder/framework (if possible)
- oop: !!! really need an empty default constructor declared in the header
- attach `CContext` to window(s) // by ref?!
- create engine (using context)
  - add viewports (windows + cameras) to engine // new `CViewport` = `CWindow` + `CCamera`

- `glx` draw something // start the ogl framework
  - engine picks the context
  - move `CContext` to ogl (since it uses only opengl) // `uix::ogl::CContext` // `uix::COGLContext` extends `ogl::CContext`
    - `CSurface` + `CCanvas` takes `CContext`(or ref) not SConfig

- timer (proper timer object w/ start & elapsed)

- move window create logic from `CWindow` to `CFrame` (first concrete child) and others
- `SConfig`: replace window hints w/ config
- `SState`: window & application states for persistance


#### Architecture
##### `Game` (app)
##### `Game Engine`
##### `Graphic Engine`
##### `Graphic Framework`
##### `...`

#### Engine
                +-----+
                |Logic|
                +-----+
                   ↓
               +--------+
               |Messager|              // routes messages to engine systems/components
               +--------+
       ↓       ↓        ↓       ↓
    +-----+ +------+ +-----+ +-----+
    |Input| |Render| |Scene| |Audio|
    +-----+ +------+ +-----+ +-----+
       ↓        ↓       ↓       ↓
               +---------+
               |Framework|
               +---------+
        ↓       ↓       ↓       ↓
    +------+ +-----+ +-----+ +-----+
    |Render| |Input| |Sound| |Utils|
    +------+ +-----+ +-----+ +-----+
       
##### `Input`                # linked: AI + Render + Logic + GUI + Loop
##### `Render`               # linked: Input + GUI + Logic + Loop
##### `GUI`    # (HUD)       # linked: Render + Audio + Logic + Input + Loop
##### `Audio`  # (Sound)     # linked: GUI + Logic + Loop
##### `Logic`  # (GameLogic) # linked: * (all)
##### `AI`                   # linked: Scene + Input + Logic + Loop
##### `Scene`                # linked: Logic + AI + Loop
##### `Loop`   # (GameLoop)  # linked: * (all)



#### Framework
###### `sys` # system/core framework # io, error, string, files
###### `alc` # audio library core # 
###### `glc` # graphic library core # opengl
###### `glm` # graphic library math # g-trunc glm or...
###### `glw` # graphic library wrappers # buffer, shader, pipeline
###### `gls` # graphic library shapes # circle, sphere
###### `glo` # graphic library objects # camera, mesh, material
###### `net` # networking library # tcp, udp, sockets, http
###### `uix` # user interface extended # wrappers for windows, controls, buttons

