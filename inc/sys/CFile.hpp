#ifndef __sys_cfile_hpp__
#define __sys_cfile_hpp__

#include "sys.hpp"

namespace sys {
  class CFile {
      // @todo: use std::filesystem
    public:
      enum EOption : sys::bitfield {
        NONE,
        OPEN   = 0b00000001,
        READ   = 0b00000010,
        WRITE  = 0b00000100,
        BINARY = 0b00001000,
        APPEND = 0b00010000,
      };
    protected:
      std::ifstream*     mStream  {nullptr}; 
      const sys::CString mFilepath; // MUST be inited
    public:
      CFile(const sys::CString& filepath, sys::bitfield eOptions = EOption::READ);
      virtual ~CFile();
    public:
      // CFile& operator =(const CString& filepath);
    public:
      void            open(sys::bitfield = EOption::READ);
      const char*     extension() const;
      std::streamsize size() const;
  };
}

#endif //__sys_cfile_hpp__
