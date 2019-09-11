#ifndef __cym_clogger_hpp__
#define __cym_clogger_hpp__

#include "cym.hpp"
#include "CSingleton.hpp"

#include <memory>

#ifndef LOGGING
// not defined...no logging
#endif//LOGGING

#ifdef LOGGING_DEBUG
#  define LOGGING_LEVEL cym::CLogger::ELevel::DEBUG
#endif//LOGGING_DEBUG
#ifdef LOGGING_INFO
#  define LOGGING_LEVEL cym::CLogger::ELevel::INFO
#endif//LOGGING_INFO
#ifdef LOGGING_WARN
#  define LOGGING_LEVEL cym::CLogger::ELevel::WARN
#endif//LOGGING_WARN
#ifdef LOGGING_ERROR
#  define LOGGING_LEVEL cym::CLogger::ELevel::ERROR
#endif//LOGGING_ERROR
#ifdef LOGGING_FATAL
#  define LOGGING_LEVEL cym::CLogger::ELevel::ERROR
#endif//LOGGING_FATAL
#ifdef LOGGING_NONE
#  define LOGGING_LEVEL cym::CLogger::ELevel::NONE
#endif//LOGGING_NONE

#ifdef LOGGING_COUT
#  define LOGGING_PROVIDER cym::CCoutLoggerProvider
#endif//LOGGING_COUT

#ifndef LOGGING_LEVEL
#  define LOGGING_LEVEL cym::CLogger::ELevel::DEBUG
#endif//LOGGING_LEVEL
#ifndef LOGGING_PROVIDER
#  define LOGGING_PROVIDER cym::CCoutLoggerProvider
#endif//LOGGING_PROVIDER

namespace cym {
  class CLogger;
  
  class CLoggerProvider {
    friend class CLogger;
    
    public:
    CLoggerProvider();
    virtual ~CLoggerProvider();
    
    public:
    virtual void log(const std::string& message) = 0;
  };
    
  class CFileLoggerProvider : public CLoggerProvider {
    public:
    virtual void log(const std::string&);
  };
  
  class CCoutLoggerProvider: public CLoggerProvider {
    public:
    virtual void log(const std::string&);
  };
  
  class CLogger : public CSingleton<CLogger> {
    public:
    enum class EManipulator: int {
      END = 0x0,
    };
    enum class ELevel      : int {
      NONE  = 0,         //  0
      FATAL = 1,         //  1
      ERROR = FATAL,     //  1
      WARN  = 2 | ERROR, //  3
      INFO  = 4 | WARN,  //  7
      DEBUG = 8 | INFO,  // 15
    };
    
    public:
    static const ELevel       nfo;
    static const ELevel       dbg;
    static const ELevel       wrn;
    static const ELevel       err;
    static const EManipulator end;
    
    protected:
    std::string      mOutput{""};
    ELevel           mLevel{LOGGING_LEVEL};
    CLoggerProvider* mProvider{new LOGGING_PROVIDER};
    
    public:
    CLogger();
    virtual ~CLogger();
    
    public:
    template <typename T> CLogger* operator << (const T& output) { return push(output); }
    friend const CLogger::ELevel& operator <<(const CLogger::ELevel&, const CLogger::EManipulator&);
    template <typename T> friend const CLogger::ELevel& operator <<(const CLogger::ELevel&, const T&);
    friend CLogger* operator <<(CLogger*, const std::string&);
    
    public:
    template <typename T> CLogger* push(const T& output) {
#if   defined(LOGGING_DEBUG)
      mLevel = ELevel::DEBUG;
#elif defined(LOGGING_INFO)
      mLevel = ELevel::INFO;
#elif defined(LOGGING_WARN)
      mLevel = ELevel::WARN;
#elif defined(LOGGING_ERROR)
      mLevel = ELevel::ERROR;
#elif defined(LOGGING_FATAL)
      mLevel = ELevel::ERROR;
#elif defined(LOGGING_NONE)
      mLevel = ELevel::NONE;
#endif//LOGGING_NONE
      std::stringstream ss;
      ss << output;
      mOutput.append(ss.str());
      return this;
    }
    
    void level(ELevel&& eLevel) { mLevel = std::move(eLevel); }
    void provider(CLoggerProvider*&& pProvider) { delete mProvider; mProvider = std::move(pProvider); }
  };
  
  template <typename T> const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const T& output) {
    CLogger::instance()->push(output);
    return type;
  }
  
  using log = cym::CLogger;
}

#endif //__cym_clogger_hpp__
