

#### TODO
- layers
- viewports | `CViewport` = `CCamera` + ???

#### Notes

#######
- fix: dds texture flipped
- fix: texture setWrapping + filtering + blending
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
  for (CModel* pModel : get_models())
    pModel->draw();
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
    | | | - CREATE depth   GL_DEPTH_COMPONENT + GL_FLOAT + BILINEAR
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
    | | | | | | - CLEAR  color & depth
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
    | | | - SET flags (cull face back, depth)
    | | | - BIND (geometry) framebuffer (depth + color + normals + motion)
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
    | | | - BIND/UNIFORM geometry.depth   framebuffer AS depth texture  
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
    | | | - (UN)SET flags (depth, stencil, blend, cull_face, back)
    | | | 
    | | | - BIND (output=0) framebuffer 
    | | | 
    | | | - BIND (lighting) shader
    | | | 
    | | | - BIND (framebuffer) geometry.depth   AS depth texture
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
    | | | - DISABLE depth & stencil
    | | | - SET final opengl flags
    | | | - BIND (output=0) framebuffer
    | | | - SET viewport (width,height of output)
    | | | - UNIFORM (framebuffer) output.color AS texture GL_TEXTURE1
    | | | - DRAW fullscreen quad
      
    
    

---    
    
    
    
    
    | - RENDER:forward
    | | - final pass
    | | | - BIND framebuffer 0
    | | | | - CLEAR color & depth 
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
    | | | | - FOR EACH join
    | | | | | - UNIFORM join.matrix
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
    
    
    
    
    























