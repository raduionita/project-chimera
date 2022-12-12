#ifndef __sys_cexception_hpp__
#define __sys_cexception_hpp__

#include "sys/sys.hpp"
#include "sys/CString.hpp"

#include <exception>
#include <ostream>

namespace sys {
  class CException : public std::exception {
    protected:
      sys::string mMessage;
      sys::string mFile;
      int         mLine;
    public:
      CException();
      CException(const sys::string&); 
      CException(const sys::string&, int);
      CException(const sys::string&, const sys::string&, int);
    public:
      CException& operator <<(const std::string&);
    public:
      virtual const char* what() const throw();
    public:
      inline CException& message(const sys::string& m) { mMessage.assign(m); return *this; }
      inline CException& file(const sys::string& f) { mFile.assign(f); return *this; }
      inline CException& line(int l) { mLine = l; return *this; }
    public:
      friend std::ostream& operator <<(std::ostream&, const CException&);
  };

  inline void throw_if(bool test, const sys::string& message, const sys::string& file = __FILE__, int line = __LINE__) {
    if (test) throw CException(message, file, line);
  }

  inline std::ostream& operator <<(std::ostream& o, const CException& e) { return o << "[EXCEPTION] [" << e.mFile << ":" << e.mLine << "] " << e.mMessage; }
} // namespace sys

#define EXCEPTION (sys::CException(__FILE__, __LINE__))

#endif // __sys_cexception_hpp__