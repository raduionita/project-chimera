#ifndef __app_h_
#define __app_h_

#include <GL/glew.h>
// #include <GL/gl3w.c>
#define  GLFW_NO_GLU 1
#define  GLFW_INCLUDE_GLCOREARB 1
#include <GL/glfw3.h>

#include <iostream>

// #include <cstdio>
// #include <cstring>

typedef bool GLbool;

namespace dae
{ 
  struct appmeta
  {
    // window
    GLchar title[128];
    GLuint windowWidth;
    GLuint windowHeight;
    GLbool fullscreen;
    GLbool cursor;
    // opengl
    GLushort minorGlVersion;
    GLushort majorGlVersion;
    GLushort samples;
    GLbool   stereo;
  };
  
  class app
  {
    public:
      app() : paused(false), running(false), window(nullptr) { }
      app(const app&) = delete;
      virtual ~app() { }
      app& operator=(const app&) = delete;
    public:
      /*                                                                                                            */
      virtual void run(int argc, char** argv)
      {
        std::cout << "dae::app::run()" << std::endl;
        app::self = this;
        
        /* init                                                                                                     */
        
        glfwSetErrorCallback(_onError);
        
        if(!glfwInit())
          return;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                         // info.majorGlVersion = 4
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                         // 4.3 need shaders to render!
        
        // #ifdef DEBUG 
          // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 1);                                      // info.samples | GLFW_FSAA_SAMPLES
        glfwWindowHint(GLFW_STEREO, GL_FALSE);                                // info.stereo
        
        // if fullscreen...
        // else
        window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
        if(!window)
        {
          glfwTerminate();
          std::cerr << "Failed to create GLFWwindow" << std::endl;
          return;
        }
        glfwMakeContextCurrent(window);
        glfwSetWindowSizeCallback(window, _onResize);
        glfwSetKeyCallback(window, _onKey);
        // glfwSetMouseButtonCallback(window, _onMouseButon);
        // glfwSetCursorPosCallback(window, _onMouseMove);
        // glfwSetScrollCallback(window, _onMouseScroll)
        // glfwSetFramebufferSizeCallback(...?...);
        // glfwSetInputMode(window, GLFW_CURSOR, 1);                           // glfwEnable(GLFW_CURSOR)
        // glfwGetWindowAttrib(window, GLFW_STEREO);
        
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
        {
          std::cerr << "Failed to init GLEW!" << std::endl;
          glfwDestroyWindow(window);
          glfwTerminate();
          return;
        }
        
        // #ifdef DEBUG
          // std::clog << "VENDOR  : " << glGetString(GL_VENDOR)   << std::endl;
          // std::clog << "VERSION : " << glGetString(GL_VERSION)  << std::endl;
          // std::clog << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;

        running = GL_TRUE;

        init();
        do {                                                        // the loop
          // glfwGetFramebufferSize(window, &width, &height);
          
          if(!paused)
          {
            tick(glfwGetTime());                                    // render && update 
            glfwSwapBuffers(window);                                // swap buffers | 
          }
          
          running = !glfwWindowShouldClose(window);                 // on window close
          glfwPollEvents();                                         // listen for events return immediatly
          // glfwWaitEvents();                                      // sleep the thread until someone triggers an event
        } while(running);
        
        glfwDestroyWindow(window);
        glfwTerminate();
        
        stop();
      }
      virtual void init() { }
      virtual void tick(const GLdouble&) { }
      virtual void stop() { }
      /*                                                                                                            */
      virtual void onKey(GLint key, GLint code, GLint action, GLint mods) { if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE); }
      virtual void onResize(GLint width, GLint height) { /* set info.window.width && info.window.height */ /* glfwSetWindowSize(window, width, height); */ }
      virtual void onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message) { /* do some debugging */ }
      /*                                                                                                            */
    protected:
      GLbool      paused;
      GLbool      running;
      GLFWwindow* window;
      static app* self;
    protected:
      static void _onKey(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mods)
      {
        app::self->onKey(key, code, action, mods);
      }
      static void _onResize(GLFWwindow* window, GLint width, GLint height) 
      { 
        app::self->onResize(width, height); 
      }
      static void APIENTRY _onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* param)
      {
        reinterpret_cast<app*>(param)->onDebug(source, type, id, severity, length, message);
      }
      static void GLFWAPI _onError(GLint error, const GLchar* message)
      {
        std::cout << "[" << error << "] " << message << std::endl;
      }
  };
  app* app::self = nullptr;
}

#define MAIN(cls)               \
int main(int argc, char** argv) \
{                               \
  cls* app = new cls();         \
  app->run(argc, argv);         \
  delete app;                   \
  return 0;                     \
}

#endif // __app_h_
