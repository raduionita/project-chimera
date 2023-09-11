#ifndef __sys_cexception_hpp__
#define __sys_cexception_hpp__

#include "sys/sys.hpp"

#include <exception>
#include <ostream>
#include <string>

namespace sys {
  class CException : public std::exception {
    protected:
      std::string mMessage;
      std::string mFile;
      int         mLine;
    public:
      CException();
      CException(const std::string&); 
      CException(const std::string&, int);
      CException(const std::string&, const std::string&, int);
    public:
      CException& operator <<(const std::string&);
    public:
      virtual const char* what() const throw();
    public:
      inline CException& message(const std::string& m) { mMessage.assign(m); return *this; }
      inline CException& file(const std::string& f) { mFile.assign(f); return *this; }
      inline CException& line(int l) { mLine = l; return *this; }
    public:
      friend std::ostream& operator <<(std::ostream&, const CException&);
  };

  inline void throw_if(bool test, const std::string& message, const std::string& file = __FILE__, int line = __LINE__) {
    if (test) throw CException(message, file, line);
  }

  inline std::ostream& operator <<(std::ostream& o, const CException& e) { return o << "[EXCEPTION] [" << e.mFile << ":" << e.mLine << "] " << e.mMessage; }
} // namespace sys

#define EXCEPTION (sys::CException(__FILE__, __LINE__))

#endif // __sys_cexception_hpp__