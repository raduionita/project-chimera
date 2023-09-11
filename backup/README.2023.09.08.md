# C++ OpenGL API Game Engine ###########################################################################################

## 2023-09-02 ##########################################################################################################

### `STRUCTURE`

```cpp
  app::CApplication : cym::CApplication
    // driver
    cym::CDriver // software =[console, window (gid), image (draw image, blit image to window)] | hardware =[opengl, directx, vulkan]
    // window
    cym::CWindow // win::CCanvas | win::CWindow | win::CConsole
      // layout
      cym::CLayout // only grid => FULL(=1.item vertial) | VERTICAL(=+2.items vertial) | HORIZONTAL (=+2.items horizontal)
        // viewports
        cym::CViewport // map | view (top|bottom, side|left, front|back)
          cym::CLayer
            // screen // = wrapper around CScene (=shareable game world descriptor)
            cym::CPixolScreen // = expects to be able to extract discreet (element) info from CScene[i][j]
              // scene (=shareable game wold descriptor)
              cym::CGlyphScene
              // render function
              void render(float dt) 
                // 
        cym::CViewport // show game
          // size
          cym::SSize // {w,h}
          // layers
          cym::CLayer // gui(menus), screen (face,hud), game
          cym::CLayer 
            // scope = [debug, intro, menu, game]
            cym::EScope {DEBUG, INTRO, MENU, GAME}
            // visibility
            bool bIsVisible // true = render | false = dont
            // screen
            cym::CRaycastScreen // type = [planar (debug,menu,sidescroll game), grid(pixel), raycast (2.5D), isometric (2D), orthogonal (3D), perspective (3D)]
              cym::CCamera
              // scene (=shareable game wold descriptor)
              cym::CGlyphScene
              // render function
              void render(float dt)
                // 


  cym::TInstance<T> // T = CScene (same scene in different windows), CMaterial, CModel...
```
### `L0GIC`
```text
  - INIT
  | - CREATE CDriver
  | - CREATE CWindow <- CDriver
  | | - CREATE CLayout, CViewport, CLayer
  | - CREATE CScene
  | | - UDPATE CScene + CApplication::STATE # + save file
  | | - INSERT CScene -> CScreenManager
  | - ATTACH CScene -> CScreen
  | - ATTACH CScreen -> CLayer


  - LOOP
  | - INPUTS  # read inputs # submit commands/instructions/messages to be processed in update
  | - UPDATE
  | | - FOREACH scene IN CSceneManager
  | | | - UPDATE scene
  | | | | FOREACH entity IN scene
  | | | | - UPDATE entity
  |
  | - RENDER 
  | | - FOREACH window IN application
  | | | - FOREACH viewport IN window
  | | | | - FOREACH layer IN viewport # in order
  | | | | | - IF layer.bIsVisible
  | | | | | | - RENDER screen TO context # use screen render logic
```


```cpp
  // renderer
    // raycast, forward, deferred

  // context 
    // con, gdi/win, img, ogl, d3d, vlk
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