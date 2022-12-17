#ifndef __sys_hpp__
#define __sys_hpp__

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
  #define DIRECTORY_SEPARATOR '\\'
  #define DS '\\'
#else
  #define DIRECTORY_SEPARATOR '/'
  #define DS '/'
#endif//_WIN32

#undef DELETE
#define DELETE(what) delete what;what=nullptr;
#define UNUSED(x)
#define ASSERT(cond) assert(cond)

namespace sys {
  class CApplication;
  class CError;
  class CException;
  class CLogger;

  template<typename T> class TPointer;
  template<typename T> class TReference;
  template<typename T> class TSingleton;
  template<typename T> class TBlock;
} // namespace sys

namespace sys {
  using exception = sys::CException;

  template<typename T> using ptr = sys::TPointer<T>;
  template<typename T> using ref = sys::TReference<T>;
} // namespace sys

struct {
    template<typename T> inline T&& operator <<(T& lval) {
        return static_cast<T&&>(lval);
    }
} RVAL;
#define rval (RVAL) <<


#endif //__sys_hpp__
