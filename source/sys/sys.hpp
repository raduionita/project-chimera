#ifndef __sys_hpp__
#define __sys_hpp__

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
  #define DIRECTORY_SEPARATOR '\\'
  #define DS '\\'
#else
  #define DIRECTORY_SEPARATOR '/'
  #define DS '/'
#endif//_WIN32

namespace sys {
  class CApplication;
  class CError;
  class CException;
  class CLogger;

  template<typename T> class TPointer;
  template<typename T> class TReference;
  template<typename T> class TSingleton;
} // namespace sys

namespace sys {
  using exception = sys::CException;

  template<typename T> using ptr = sys::TPointer<T>;
  template<typename T> using ref = sys::TReference<T>;
} // namespace sys


#endif //__sys_hpp__
