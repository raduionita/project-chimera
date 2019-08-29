// #define DEBUG 1
#include "inc/app.h"
 
class main : public dae::app
{
  public:
    void init()
    {
      std::cout << "main::init()" << std::endl;
      
      
      auto cube = dae::model::load("models\\cube.obj"); 
      
    } 
    void tick(const GLdouble& time)
    {
      std::cout << "main::tick(" << time << ")" << std::endl;
      glViewport( 0, 0, 800, 600);
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
      
      
    }
    void stop()
    {
      std::cout << "main::stop()" << std::endl;
    }
    
    /*                                                                                                              */
    
    void onKey(GLint key, GLint code, GLint action, GLint mods)
    {
      std::clog << "main::onKey("<< key << ", " << action << ")" << std::endl;
      
      switch(key)
      {
        case GLFW_KEY_SPACE:
        {
          if(action == GLFW_PRESS)
            paused = paused ? false : true;
          break;
        }
        case GLFW_KEY_ESCAPE:
        {
          if(action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);   
          break;
        }
      }
    }
};

MAIN(main);
