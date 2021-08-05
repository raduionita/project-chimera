#ifndef __sys_hpp__
#define __sys_hpp__

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <map>      // for (const auto& [k,v] : map)
#include <set>
#include <array>
#include <algorithm>
#include <memory>
#include <functional>

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
#define UNUSED(x)

namespace sys { 
  class CApplication;
  class CError;
  class CException;
  class CFile;
  class CLogger;
  class CMemory;
  class CTimer;
  class CStream;
  enum EPointer { SHARED = 1, WEAK = 2, UNIQUE = 2 };
  template<typename T, EPointer E> class TPointer;
  template<typename T> class CEntry;
  template<typename T> class CRegistry;
  template<typename T> class TSingleton;
  template<typename T, typename A> class TBlock;
  template <typename T> class TIterator;
  class CThreader;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> class CType {
    public:
      typedef T class_type;
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  typedef char          byte;
  typedef unsigned char ubyte;
  typedef int8_t        tiny;
  typedef uint8_t       utiny;
  typedef uint16_t      ushort;
  typedef uint32_t      uint;
  typedef union {
    byte* pointer;
    intptr_t address;
  }   buffer;
  typedef uint          bitfield;
  typedef unsigned long ulong;
  
  using CString                  = std::string;
  template<typename V> using CSet                 = std::set<V>;
  template<typename K, typename V> using CMap               = std::map<K,V>;
  template<typename K, typename V> using CTable             = std::map<K,V>;
  template<typename L, typename R> using CPair              = std::pair<L,R>;
  template<typename V> using CVector              = std::vector<V>;
  template<typename V> using CCollection          = std::vector<V>;
  template<typename V, std::size_t S> using CArray = std::array<V,S>;
  
  template<typename T, typename A = std::allocator<T>> using block = sys::TBlock<T,A>;
  using file        = sys::CFile;
  using stream      = sys::CStream;
  using exception   = sys::CException;
  template<typename T> using ptr     = sys::TPointer<T, EPointer::SHARED>;
  template<typename T> using spo     = sys::TPointer<T, EPointer::SHARED>;
  template<typename T> using wpo     = sys::TPointer<T, EPointer::WEAK>;
  template<typename T> using upo     = sys::TPointer<T, EPointer::UNIQUE>;
  
  
  using string                  = std::string;
  template<typename V> using set                 = std::set<V>;
  template<typename K, typename V> using map               = std::map<K,V>;
  template<typename K, typename V> using table             = std::map<K,V>;
  template<typename L, typename R> using pair              = std::pair<L,R>;
  template<typename V> using vector              = std::vector<V>;
  template<typename V, std::size_t S> using array = std::array<V,S>;
  
  // usage: (64byte aligned)
  // buffer data;
  // byte*  temp = new byte[1000+63]           // create big chung of memory + padding
  // data.pointer = temp+63;                   // assign & offset pointer by 63bytes
  // data.address = data.address & (-(int)64); // back to the front
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> inline std::string concat(const char* text, T frag) { std::ostringstream os; os << text << frag; return os.str(); }
    
  inline int64_t now() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }
  
  inline std::string trim(const std::string& str) {
    std::string out;
    out.reserve(str.size());
    for(size_t i = 0, j = 0; i < str.size(); ++i) {
      const char& ch = str[i];
      if(ch != '\t' && ch != ' ' && ch != '\n')
        out[j++] = ch;
    }
    out.shrink_to_fit();
    return out;
  }
  
  inline bool strncmp(const char* lhs, const char* rhs, uint n) { for (uint i = 0; i < n; i++) if (lhs[i] != rhs[i]) return false; return true; }
  
  inline bool isnewline(const char& ch) { return (ch == '\n' || ch == '\r' || ch == '\0'); }
  
  template<typename K, typename V> inline bool find(const K& k, const sys::CMap<K,V>& m, V& b) { auto i{m.find(k)}; if (i != m.end()) { b = i->second; return true;} return false; } 
  
  template<typename K, typename V, typename E> inline V& find_or_throw(const K& k, sys::CMap<K,V>& m, const E& e) { auto i{m.find(k)}; if (i == m.end()) { throw e; } return i->second; }
  
  inline uint alnumspn(const char* src) { uint i {0}; while(!isalnum(src[i])) i++; return i; }  
  
  inline uint charspn(const char* src, char c) { uint i {0}; while(src[i] != c) i++; return i; }
  
  /* like std::to_string, but w/ precission, so u can control the output length */
  template <typename T> inline std::string to_string(const T v, const int p = 6) {
    std::ostringstream out;
    out.precision(p);
    out << std::fixed << v;
    return out.str();
  }
  
  inline std::string to_hex(const uint64_t d) { std::stringstream sss; sss << "0x" << std::hex << d; return sss.str(); }
  
  // using namespace std::chrono_literals;
  // auto day = 24h;
}

#endif //__sys_hpp__
