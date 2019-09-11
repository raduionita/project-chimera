#ifndef __cym_cexception_hpp__
#define __cym_cexception_hpp__

#include "cym.hpp"

#include <exception>
#include <string>
#include <ostream>

namespace cym {
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

#define EXCEPTION (cym::CException(__FILE__, __LINE__))

#endif //__cym_cexception_hpp__
