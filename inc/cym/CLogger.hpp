#ifndef __cym_clogger_hpp__
#define __cym_clogger_hpp__

#include "cym.hpp"
#include "CSingleton.hpp"

#include <memory>

#ifndef CYM_LOGGER
// not defined...no logging
#endif//CYM_LOGGER

#ifdef CYM_LOGGER_DEBUG
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::DEBUG
#endif//CYM_LOGGER_DEBUG
#ifdef CYM_LOGGER_INFO
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::INFO
#endif//CYM_LOGGER_INFO
#ifdef CYM_LOGGER_WARN
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::WARN
#endif//CYM_LOGGER_WARN
#ifdef CYM_LOGGER_ERROR
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::ERROR
#endif//CYM_LOGGER_ERROR
#ifdef CYM_LOGGER_FATAL
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::ERROR
#endif//CYM_LOGGER_FATAL
#ifdef CYM_LOGGER_NONE
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::NONE
#endif//CYM_LOGGER_NONE

#ifdef CYM_LOGGER_COUT
#  define CYM_LOGGER_PROVIDER cym::CCoutLoggerProvider
#endif//CYM_LOGGER_COUT

#ifndef CYM_LOGGER_LEVEL
#  define CYM_LOGGER_LEVEL cym::CLogger::ELevel::DEBUG
#endif//CYM_LOGGER_LEVEL
#ifndef CYM_LOGGER_PROVIDER
#  define CYM_LOGGER_PROVIDER cym::CCoutLoggerProvider
#endif//CYM_LOGGER_PROVIDER

namespace cym {
#ifdef CYM_LOGGER
  constexpr bool LOGGER {true};
#else // CYM_LOGGER
  constexpr bool LOGGER {false};
#endif//CYM_LOGGER
  
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
      std::string      mOutput   {""};
      ELevel           mLevel    {CYM_LOGGER_LEVEL};
      CLoggerProvider* mProvider {nullptr};
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
#if   defined(CYM_LOGGER_DEBUG)
      mLevel = ELevel::DEBUG;
#elif defined(CYM_LOGGER_INFO)
      mLevel = ELevel::INFO;
#elif defined(CYM_LOGGER_WARN)
      mLevel = ELevel::WARN;
#elif defined(CYM_LOGGER_ERROR)
      mLevel = ELevel::ERROR;
#elif defined(CYM_LOGGER_FATAL)
      mLevel = ELevel::ERROR;
#elif defined(CYM_LOGGER_NONE)
      mLevel = ELevel::NONE;
#endif//CYM_LOGGER_NONE
      std::stringstream ss;
      ss << output;
      mOutput.append(ss.str());
      return this;
    }
    public: // get&set
      void   level(ELevel&& eLevel) { mLevel = std::move(eLevel); }
      ELevel level()                { return mLevel; }
      void             provider(CLoggerProvider*&& pProvider) { delete mProvider; mProvider = std::move(pProvider); }
      CLoggerProvider* provider() { if (!mProvider) mProvider = new CYM_LOGGER_PROVIDER; return mProvider; }
  };
  
  template <typename T> const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const T& output) {
    CLogger::instance()->push(output);
    return type;
  }
  
  using log = cym::CLogger;
}

#endif //__cym_clogger_hpp__
