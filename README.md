# C++ OpenGL API Game Engine ###########################################################################################

## 2023-09-02 ##########################################################################################################

### `structure`
```c++


```
###
```c++

// update
  cym::CInputManager::update(float dt)
    // CREATE input map
    // FOR EACH layer=handler IN screen.layers
      // game layer HANDLE input
        // SUBMIT [move::front|back|left|right] input message(s)
        // SUBMIT [look::up|down|left|right] input message(s)
        // SUBMIT [move::up|down] (=jump) input message(s)
      // tool layer HANDLE input
        // SUBMIT [play animation] input message
      // edit layer HANDLE input
        // SUBMIT [hover] (hightlight node)
        // SUBMIT [drag = MLbDown + MMove] 
        // SUBMIT [select = MLbDown + MLbUp] // 
        // SUBMIT (camera) [move:xyz] [?]
        // SUBMIT (camera) [rotate:xyz] [MRbDown + MMove]

  cym::CControllerManager::update(float dt);
    // FOR EACH controller IN
      // UPDATE controller

  cym::CIntersectResolver::update(float dt);
    // 

// render
  cym::CSreenManager::render(float dt);
    // FOR EACH window IN windows
      // FOR EACH layer in window.screen.layers
        // RENDER layer

// screen

+ screen
  + layer::logo
  + layer::intro
  + layer::debug
  + layer::prompt "terminal"
  + layer::load
  + layer::menu
  + layer::tool      +layer::info
  + layer::edit      +layer::play

// scene
// 3rd player-controllerd human rider + weapon + in rain + talking + shooting + driving + riding a bike

+ node::scene
  + controller::node ??

  + node::force name="push"
    + controller::node
    | + on::tick // update position of linked node::model(s)
    |
    + force name="repulsor"
    |
    + node::joint "root"
      + node::model ref="bike"
    
  + node::effect name="rain"
    + controller::node
    | + on::goin // attach rain effect (particle drops + wet material) to the node
    | + on::tick // update rain effects for all nodes
    | + on::exit // detach effect + material from the node
    |
    + effect name="rain"
    | 
    + node::joint "root"
      + node::model ref="bike"
      + node::model ref="rider"

  + node::model "bike"
    + controller::node
    | + 
    |
    + model name="bike"
    | + skeleton
    | + material
    |    
    + node::joint "root"
      + node::model "rider" link::loose
      | + controller
      | |
      | + model name="rider"
      | | + skeleton 
      | | + material 
      | |  
      | + node::joint [root]
      |   + node::camera name="camera" link::loose
      |     + camera name="camera"
      |   + node::joint [arm]
      |     + node::joint [hand]
      |       + node::model name="weapon"
      |         + controller::node
      |         | 
      |         + model name="weapon"
      |  
      + node::joint name="wheel-front"
      | + node::model name="wheel"
      |   + model name="wheel"
      |
      + node::joint name="wheel-back"
        + controller::node
```




### `Research`
- `Game Programming Patterns` (by Robert Nystrom)
- `Game Coding Complete`
- `Game Engine Architecture` (by Jason Gregory)
- `enginuity` (gamedev.new)
- `https://github.com/SFML/SFML/wiki/Tutorial:-Basic-Game-Engine`
- `http://www.stuartmathews.com/index.php/gaming/938-a-simple-game-engine-architecture`
- `https://youtu.be/L19dBX53M5M` (bennybox)
- `https://gamasutra.com/blogs/MichaelKissner/20151027/257369/Writing_a_Game_Engine_from_Scratch__Part_1_Messaging.php`