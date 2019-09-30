#ifndef __cym_hpp__
#define __cym_hpp__

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#define RETURNCN(cond)      if(cond)return
#define RETURNCV(cond,val)  if(cond)return val
#define GET3RDARG(arg0,arg1,arg2,...) arg2
#define CHOOSERETURN(...)   GET3RDARG(__VA_ARGS__, RETURNCV, RETURNCN,)
#define RETURN(...)         CHOOSERETURN(__VA_ARGS__)(__VA_ARGS__)
#define IF(cond,action)     if(cond)action
#define WHILE(cond,action)  while(cond)action
#define BREAK(cond)         if(cond)break
#define CONTINUE(cond)      if(cond)continue
#undef  DELETE
#define DELETE(what)        delete what;what=nullptr

namespace cym { 
  
  typedef uint32_t uint;
  typedef int8_t   byte;
  typedef uint8_t  ubyte;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
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
  
  // using namespace std::chrono_literals;
  // auto day = 24h;
  
  
}

#endif //__cym_hpp__
