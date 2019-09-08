#ifndef __cym_hpp__
#define __cym_hpp__

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

namespace cym { 
  template <typename T> inline std::string concat(const char* text, T frag) { std::ostringstream os; os << text << frag; return os.str(); }
    
  inline int64_t now() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }
  
  inline std::string trim(const std::string& str)
  {
    std::string out;
    out.reserve(str.size());
    for(size_t i = 0, j = 0; i < str.size(); ++i)
    {
      const char& ch = str[i];
      if(ch != '\t' && ch != ' ' && ch != '\n')
        out[j++] = ch;
    }
    out.shrink_to_fit();
    return out;
  }
}

#endif //__cym_hpp__
