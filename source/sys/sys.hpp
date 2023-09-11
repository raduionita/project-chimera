#ifndef __sys_hpp__
#define __sys_hpp__

// directory separator
#if defined(PLATFORM_WINDOWS)
  #define DIRECTORY_SEPARATOR '\\'
  #define DS '\\'
#else
  #define DIRECTORY_SEPARATOR '/'
  #define DS '/'
#endif//_WIN32

namespace sys {
  class CExecutable;
    class CApplication;
  class CError;
  class CException;
  class CLogger;


  
} // namespace sys

#endif //__sys_hpp__