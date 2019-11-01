#ifndef __cexception_hpp__
#define __cexception_hpp__

#include "sys.hpp"

#include <exception>
#include <string>
#include <ostream>

namespace sys {
  class CException : public std::exception {
    protected:
      std::string mMessage;
      std::string mFile;
      int         mLine;
    public:
      CException();
      CException(const std::string&); 
      CException(const std::string&, const std::string&, int);
      CException(const std::string&, int);
    public:
      CException& operator <<(const std::string&);
    public:
      virtual const char* what() const throw();
    public:
      CException& message(const std::string&);
      CException& file(const std::string&);
      CException& line(int);
    public:
      friend std::ostream& operator <<(std::ostream&, const CException&);
  };
}

#define EXCEPTION (CException(__FILE__, __LINE__))

#endif //__cexception_hpp__
