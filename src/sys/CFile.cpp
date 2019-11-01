#include "sys/CFile.hpp"
#include "sys/CException.hpp"

#include <fstream>

namespace sys {
  CFile::CFile(const sys::CString& filepath, sys::bitfield eOptions) : mFilepath{filepath} {
    if (eOptions & EOption::OPEN) {
      open(eOptions);
    }
  }
  
  CFile::~CFile() {
    delete mStream;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CFile::open(sys::bitfield eOptions) {
    std::ifstream::openmode mode; 
    (eOptions & EOption::READ)   && (mode |= std::ifstream::in);
    (eOptions & EOption::WRITE)  && (mode |= std::ifstream::out);
    (eOptions & EOption::BINARY) && (mode |= std::ifstream::binary);
    (eOptions & EOption::APPEND) && (mode |= std::ifstream::app);
    mStream = new std::ifstream(mFilepath, mode);
    if (mStream->bad()) {
      throw sys::CException("Could not open "+ mFilepath);
    }
  }
  
  const char* CFile::extension() const {
    return &mFilepath[mFilepath.find_last_of('.')];
  }
  
  std::streamsize CFile::size() const {
    return mStream ? mStream->gcount() : 0;
  }
}
