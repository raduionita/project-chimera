## C++ OpenGL API Game Engine

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


### Bugs
- an event doesn't trigger properly, don't remember which one :/

### Architecture
##### `Game` (app)
##### `Game Engine`
##### `Graphic Engine`
##### `Graphic Framework`
##### `...`

### Engine
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
- messaging
  - messenger queue: too many messages this frame? queue them for the next one | control game fps
  - messenger handle messages w/ priority: 0 = now | 10+ = later
- memory:
  - fragmentation?!
  - use cpu L* cache levels
  - allocator // stack-based vs pool-based vs (multi)FRAME-based
    - frame-based: gets reset on each(or nth) frame

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

### Edit(or) App
- layouts: [4xViewports] | [2xLeft + 1xRight] | [1xRight + 2xLeft] | [1xTop + 1xBottom] | [1xViewport]
- viewport projection: [perspective] | [orthographic] 
- play mode: opens a canvas w/ shared context that plays the game

### Play(Game) App
- layout: [1xViewport] using canvas
