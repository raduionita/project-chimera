#ifndef __sys_ccollection_hpp__
#define __sys_ccollection_hpp__

#include <vector>

namespace sys {
  template <typename T> class CCollection {
      typedef T              value_type;
      typedef std::vector<T> container_type;
    protected:
      std::vector<T> mData;
  };
}

#endif //__sys_ccollection_hpp__
