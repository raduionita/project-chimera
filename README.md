# C++ OpenGL API Game Engine ###########################################################################################

## 2023-09-02 ##########################################################################################################

### `STRUCTURE`

```cpp
  app::CApplication : cym::CApplication
    // window // CCanvas, CWindow, CImage?, CConsole
    cym::CWindow
      // layout
      cym::CLayout
        // screens // // grid | view (top|bottom, side|left, front|back)
        cym::CScreen 
          // layers // vector<CLayer>
          cym::CLayer
          cym::CLayer
            // scene
            cym::CScene
                //
    void onKeyPress()
      // CEventManager::commit(CInputEvent)
      // remember CInputEvent (MOUSE or KEYBOARD)
    void update()
      // input phase
      // CEventManager::update()
      // CControllerMaanger::update()



  cym::CLayer : cym::CEventListener
    // can receive evnts
    // translates CEvent to CMessage => CMessageCoordinator
  cym::CDebugLayer : cym::CLayer 
  cym::CConsoleLayer : cym::CLayer
  cym::CMenuLayer : cym::CLayer
  cym::CHUDLayer : cym::CLayer
  cym::CGameLayer : cym::CLayer
  
  cym::CEventManager
    // events
    cym::CEvent
    cym::CEvent
    // listeners
    cym::CListener
    cym::CListener
    // update // on loop match event w/ listener
    void update()
      // for each listener
        // for each input event
          // send message to an listener (if active)

  cym::CMessageCoordinator
    // update // send message to listeners
    void submit(cym::CMessage)
      // send message to CController

  cym::CControllerManager
    // controllers
    cym::CController
    cym::CController
    // update // process all controllers
    void update(float dt)
      // for each controller : update

  cym::TController<T> // TController<CMenu>, TController<CScene>, CEntityController
    // entity being controllerd
    cym::CEntity
    // messages
    cym::CMessage // cym::CWalkMessage (move + animate)
    cym::CMessage
    // update // process all messages
    void update(float dt)
      // for each message : process


  cym::TInstance<T> // T = CScene (same scene in different windows), CMaterial, CModel...
```
### `L0GIC`
```text
  - INIT
  | -


  - LOOP
  | - INPUTS
  | |
  |
  | - UPDATE
  | | 
  |
  | - RENDER 
  | | 
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