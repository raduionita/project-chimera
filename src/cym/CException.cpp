#include "cym/CException.hpp"

namespace cym {
  CException::CException() : std::exception() {  }
  
  CException::CException(const std::string& message) : mMessage{message} { } 
  
  CException::CException(const std::string& message, const std::string& file, int line) : mMessage{message}, mFile{file}, mLine{line} { }
  
  CException::CException(const std::string& file, int line) : mFile{file}, mLine{line} { }

  CException& CException::operator <<(const std::string& message) { mMessage.append(message); return *this; }

  const char* CException::what() const throw() { return mMessage.c_str(); }

  CException& CException::message(const std::string& message) { mMessage = message; return *this; }
  CException& CException::file(const std::string& file)       { mFile = file; return *this; }
  CException& CException::line(int line)                      { mLine = line; return *this; }
  
  std::ostream& operator <<(std::ostream& o, const CException& e) { return o << "[EXCEPTION] [" << e.mFile << ":" << e.mLine << "] " << e.mMessage; }
}
