#ifndef __sys_cfile_hpp__
#define __sys_cfile_hpp__

#include "sys/sys.hpp"
#include "CLogger.hpp"

#include <fstream>

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
      mutable std::ifstream* mStream  {nullptr}; 
              sys::CString   mFilepath; // MUST be inited
    public:
      CFile();
      CFile(const sys::CString& filepath, sys::bitfield eOptions = EOption::READ);
      CFile(const char*         filepath, sys::bitfield eOptions = EOption::READ);
      CFile(sys::CString&&      filepath, sys::bitfield eOptions = EOption::READ);
      CFile(char*&&             filepath, sys::bitfield eOptions = EOption::READ);
      CFile(const sys::CFile&);
      virtual ~CFile();
    public:
      CFile& operator =(const sys::CString& filepath);
      CFile& operator =(const char*         filepath);
      friend CString operator +(const char* text, const CFile& file);
    public:
      explicit inline operator CString()             { return mFilepath; }
      explicit inline operator const CString() const { return mFilepath; }
    public:
      inline void            read(char* data, std::streamsize len) const { mStream->read(data, len); }
      inline bool            good() const { return mStream ? mStream->good() : false; }
      inline bool            fail() const { return !good(); }
      inline std::streamsize size()      const { return mStream ? mStream->gcount() : 0; }
      inline bool            empty()     const { return mFilepath.empty(); }
      inline const char*     extension() const { return &mFilepath[mFilepath.find_last_of('.')+1]; }
      inline const char*     ext() const { return extension(); }
      inline const char*     path() const { return mFilepath.c_str(); }
      inline const char*     file() const { return &mFilepath[mFilepath.find_last_of('/')+1]; } 
    public:
      bool                   open(sys::bitfield = EOption::READ) const;
  };
  
  inline const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const CFile& file) {
    CLogger::instance()->push(file.path());
    return type;
  }
}

#endif //__sys_cfile_hpp__
