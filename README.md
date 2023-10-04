# C++ OpenGL API Game Engine ###########################################################################################

## 2023-09-02 ##########################################################################################################

### `structure`
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


// scene
// 3rd player-controllerd human rider + weapon + in rain + talking + shooting + driving + riding a bike

+ node::root
  + node::scene [hidden]
  | + data::scene
  + node::scene [active]
    |
    + node::gizmo "tool"
      + node::node [root]
        + data::node
          + node::model ref="bike" link::tight
    |
    + node::model "planet"
      + data::model "planet"
      | + model
      |   + material
      |
      + node::node [root]
        + data::node
          + node::force name="push"
            + data::force [circular] name="repulsor"
            |
            + node::node "root"
              + node::model ref="bike"
    |  
    + node::entity name="storm"
      + data::node
        + node::node
        | + data::node
        |   + node::effect "rain"
        |     + data::effect
        |       + effect
        + node::node      
          + data::node
            + node::force "push"
              + data::force
                + force
    |
    + node::model "carrige"
      + data::model name="carrige"
      | + model name="carrige"
      |   + skeleton
      |   + material
      |    
      + node::node "horse"
      | + data::node
      |   + node::model "horse"
      |     + model "horse"
      + node::node "rider"
        + data::node "rider&camera"
        | + node::node
        |   + node::node "rider"
        |   | + data::node
        |   |   + node::model "rider" link::loose
        |   |     + data::model name="rider"
        |   |     | + model
        |   |     |   + skeleton 
        |   |     |   + material 
        |   |     + node::node [root]
        |   |       + node::node [arm]
        |   |         + node::node [hand]
        |   |           + data::node "weapon"
        |   |             + node::model name="weapon"
        |   |               + data::model name="weapon"
        |   |
        |   + node::node "camera"
        |     + data::node
        |       + node::camera name="camera" link::loose
        |         + data::camera name="camera"
        |  
        + node::node name="wheel-front"
        | + data::node
        |   + node::model name="wheel"
        |     + data::model name="wheel"
        |
        + node::node name="wheel-back"
    |
    + node::node "army"
      + node::node [root]
        + node::node "root"
          + data::node "dust"
            + node::effect "dust"
        + node::node "root"
          + data::node "soldier"
            + node::model "soldier"
        + node::node "root"
          + data::node "soldier"
            + node::model "soldier"
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



    CWindow
       |
       | (mouse event)
       |
       v
     CLayer (on:mouse)
       |
       | (message)
       |
       v
  CController (on:message)          CController
       |                                 |
       |                                 |
       |                                 |
       v                                 v
     CModel                            CModel
       
