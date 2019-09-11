#ifndef __cym_cstring_hpp__
#define __cym_cstring_hpp__

#include <string>

namespace cym { 
  using CString    = std::string;
  
  inline CString T(const char* text) { return CString(text); }
  inline CString T(int num)          { return std::to_string(num); }
}

#endif //__cym_cstring_hpp__
