#ifndef __utils_h_
#define __utils_h_

namespace dae
{
  namespace utils
  {
    static inline bool isNewLine(const char& ch)
    {
      return (ch == '\n' || ch == '\r' || ch == '\0');
    }
    
    static inline bool isSpace(const char& ch)
    {
      return (ch == ' ' || ch == '\t');
    }
    
    static inline bool isEmpty(const char& ch)
    {
      return isSpace(ch) || isNewLine(ch);
    }
  }
}


#endif // __utils_h_
