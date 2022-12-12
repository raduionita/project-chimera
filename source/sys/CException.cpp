#include "sys/CException.hpp" 

namespace sys {
  CException::CException() { }
  
  CException::CException(const std::string& m) : mMessage{m} { } 
  
  CException::CException(const std::string& f, int l) : mFile{f}, mLine{l} { }
  
  CException::CException(const std::string& m, const std::string& f, int l) : mMessage{m}, mFile{f}, mLine{l} { }

  CException& CException::operator <<(const std::string& m) { mMessage.append(m); return *this; }

  const char* CException::what() const throw() { return mMessage.c_str(); }
} // namespace sys
