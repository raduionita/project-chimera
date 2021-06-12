#include "sys/CFile.hpp"
#include "sys/CException.hpp"

namespace sys {
  CFile::CFile() {
    
  }
  
  CFile::CFile(const sys::CString& filepath, sys::bitfield eOptions/*=EOption::READ*/) : mFilepath{filepath} {
    if (eOptions & EOption::OPEN) {
      open(eOptions);
    }
  }
  
  CFile::CFile(const char* filepath, sys::bitfield eOptions/*=EOption::READ*/) : mFilepath{filepath} {
    if (eOptions & EOption::OPEN) {
      open(eOptions);
    }
  }
  
  CFile::CFile(sys::CString&& filepath, sys::bitfield eOptions/*=EOption::READ*/) : mFilepath{std::move(filepath)} {
    if (eOptions & EOption::OPEN) {
      open(eOptions);
    }
  }
  
  CFile::CFile(char*&& filepath, sys::bitfield eOptions/*=EOption::READ*/) : mFilepath{std::move(filepath)} {
    if (eOptions & EOption::OPEN) {
      open(eOptions);
    }
  }
  
  CFile::CFile(const sys::CFile& that) {
    if (this != &that) {
      mFilepath = that.mFilepath;
      if (mStream != nullptr) {
        delete mStream;
      }
      if (that.mStream != nullptr) {
        mStream = new std::ifstream(mFilepath);
        mStream->flags(that.mStream->flags());
      }
    }
  }
  
  CFile::~CFile() {
    close();
    delete mStream;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CFile& CFile::operator =(const sys::CString& filepath) {
    mFilepath = filepath;
    return *this;
  }  
  
  CFile& CFile::operator =(sys::CString&& filepath) {
    mFilepath = std::move(filepath);
    return *this;
  }
  
  CFile& CFile::operator =(const char* filepath) {
    mFilepath = filepath;
    return *this;
  }
  
  CString operator +(const char* text, const CFile& file) {
    return CString(text) + file.mFilepath;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CFile::open(sys::bitfield eOptions) {
    if (mStream == nullptr) {
      std::ifstream::openmode mode;
      (eOptions & EOption::READ)   && (mode |= std::ifstream::in);
      (eOptions & EOption::WRITE)  && (mode |= std::ifstream::out);
      (eOptions & EOption::BINARY) && (mode |= std::ifstream::binary);
      (eOptions & EOption::APPEND) && (mode |= std::ifstream::app);
      mStream = new std::ifstream(mFilepath, mode);
    }
    return mStream->good();
  }
  
  bool CFile::close() {
    bool bClosable = mStream != nullptr;
    if (bClosable)
      mStream->close();
    return bClosable;
  }
}
