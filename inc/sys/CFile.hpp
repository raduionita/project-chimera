#ifndef __sys_cfile_hpp__
#define __sys_cfile_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"

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
      typedef std::ifstream stream_type;
    protected:
      mutable std::ifstream* mStream  {nullptr}; 
              sys::string    mFilepath; // MUST be inited
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
      CFile& operator =(sys::CString&& filepath);
      CFile& operator =(const char*         filepath);
      friend CString operator +(const char* text, const CFile& file);
    public:
      explicit inline operator CString()             { return mFilepath; }
      explicit inline operator const CString() const { return mFilepath; }
    public:
      // open/close
      bool                   open(sys::bitfield = EOption::READ|sys::CFile::BINARY);
      bool                   close();
      // state
      inline bool            good() const { return mStream ? mStream->good() : false; }
      inline bool            fail() const { return !good(); }
      inline std::streamsize size()      const { mStream->seekg(0,std::ios::end); std::streamsize len = mStream->tellg(); mStream->seekg(0,std::ios::beg); return len; }
      inline bool            empty()     const { return mFilepath.empty(); }
      // path
      inline std::string_view folder()    const { return std::string_view(mFilepath).substr(0,mFilepath.find_last_of('/')+1); /* mFilepath.substr(0,mFilepath.find_last_of('/')+1);*/ }
      inline const char*      ext()       const { return extension(); }
      inline const char*      extension() const { return &mFilepath[mFilepath.find_last_of('.')+1]; }
      inline const sys::string& path()      const { return mFilepath; }
      inline const sys::string& fullpath()  const { return mFilepath; }
      inline const char*     file()      const { return &mFilepath[mFilepath.find_last_of('/')+1]; } 
      inline const char*     filename()  const { return &mFilepath[mFilepath.find_last_of('/')+1]; } 
      // read
      inline void            read(byte* data, std::streamsize len) const { mStream->read(data, len); };
      inline void            line(byte* data, std::streamsize len) const { mStream->getline(data,len); }      
      inline int             peek() const { return mStream->peek(); } 
      inline void            seek(std::streamoff off) { mStream->seekg(off, std::ios::beg); }
      inline void            begin()                  { mStream->seekg(0, std::ios::beg); }
      inline void            end()                    { mStream->seekg(0, std::ios::end); }
      inline bool            eof() const              { return mStream->peek() == EOF; }
  };
  
  inline const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const CFile& file) {
    CLogger::getSingleton()->push(file.path());
    return type;
  }
}

#endif //__sys_cfile_hpp__
