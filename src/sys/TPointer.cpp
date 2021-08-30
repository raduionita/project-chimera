#include "sys/TPointer.hpp"

namespace sys {
  sys::table<intptr_t,uint32_t*> CPointer::sPointers;
  
  void CPointer::reg(void* p, uint32_t*& c) {
    auto i {intptr_t(p)};
    auto it {sPointers.find(i)};
    if (it != sPointers.end()) {
      c = it->second;
      (*c)++; 
    } else {
      sPointers.insert(sys::pair<intptr_t,uint32_t*>{i,c = new uint32_t{1}});
    }
  }
  
  bool CPointer::unr(void* p) {
    return sPointers.erase((intptr_t)p) > 0;
  }
}
