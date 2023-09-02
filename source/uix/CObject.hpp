#ifndef __uix_cobject_hpp__
#define __uix_cobject_hpp__

#ifdef PLATFORM_WINDOWS

#include "uix/uix.hpp"

namespace uix {
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
} // namespace uix

#endif // PLATFORM_WINDOWS

#endif // __uix_cobject_hpp__