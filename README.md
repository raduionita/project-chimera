# C++ OpenGL API Game Engine

## 2023-09-02 #########################################################################################################

### EDIT

```cpp
app::CApplication
  cym::CScreen
    // window
    uix::CConsole : uix::CWindow // window
    // layers
    cym::CLayer // layers

    cym::CLayer // raycast layer
      cym::CCamera
      cym::CScene

  // context
    // console
    // window (gdi)
    // opengl
    // directx
    // vulkan

  // renderer
    // raycast
    
    // forward
    // deferred


  cym::CScreen
    uix::CCanvas : uix::CWindow // main (gdi,ogl,d3d,vlk)
    cym::CLayer // game 
      cym::CViewport
        cym::CCamera
        cym::CScene
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