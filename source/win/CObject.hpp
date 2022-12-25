#ifndef __win_cobject_hpp__
#define __win_cobject_hpp__

#ifdef PLATFORM_WINDOWS

#include "win/win.hpp"

namespace win {
  class CObjectRegistry {
    public:
      CObjectRegistry() = default;
      ~CObjectRegistry();
    public:
      void insert(CObject* pObject);
      void remove(CObject* pObject);
  };

  class CObject {
    public:
      CObject() = default;
      virtual ~CObject() = default;
  };
} // namespace win

#endif // PLATFORM_WINDOWS

#endif // __win_cobject_hpp__