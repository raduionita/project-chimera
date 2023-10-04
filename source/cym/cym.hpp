#ifndef __cym_hpp__
#define __cym_hpp__

#include "sys/TPointer.hpp"
#include "sys/TSingleton.hpp"

namespace cym {
  class CApplication;
  class CManager;

  class CDriver;
  class CWindow;
  class CScreen;
  class CLayer;

  class CMessage;
  class CMessageSupervisor;

  class CModifier;
  class CProcess;
  class CController;
  class CControllerManager;
  
  class CScene;
  class CNode;

  // gl data wrappers
  class CModel;
  class CShape;
  class CMaterial;
  class CTexture;
} // namespace cym

#endif //__cym_hpp__