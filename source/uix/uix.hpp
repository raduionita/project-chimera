#ifndef __uix_hpp__
#define __uix_hpp__

namespace uix {
  class CApplication;
} // namespace uix

#endif //__uix_hpp__


#if defined(__GNUC__) || defined(__MINGW32__)
  #define ENVIRONMENT  ="mingw"
#elif defined(__CYGWIN__)
  #define ENVIRONMENT  ="cygwin"
#endif//mingw

#if defined(_WIN32)
  #define PLATFORM "windows" // Windows
#elif defined(_WIN64)
  #define PLATFORM "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
  #define PLATFORM "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
  #define PLATFORM "android" // Android (implies Linux, so it must come first)
#elif defined(__linux__)
  #define PLATFORM "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
  #include <TargetConditionals.h>
  #if TARGET_IPHONE_SIMULATOR == 1
      #define PLATFORM "ios" // Apple iOS
  #elif TARGET_OS_IPHONE == 1
      #define PLATFORM "ios" // Apple iOS
  #elif TARGET_OS_MAC == 1
      #define PLATFORM "osx" // Apple OSX
  #endif
#else
  #define PLATFORM NULL
#endif