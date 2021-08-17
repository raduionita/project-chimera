#ifndef __sys_clogger_hpp__
#define __sys_clogger_hpp__

#include "sys/sys.hpp"
#include "sys/TSingleton.hpp"

#include <memory>

#ifndef SYS_LOGGER
  // no logging
#endif//SYS_LOGGER

#ifdef SYS_LOGGER_DEBUG
#  define SYS_LOGGER_LEVEL CLogger::ELevel::DEBUG
#endif//SYS_LOGGER_DEBUG
#ifdef SYS_LOGGER_INFO
#  define SYS_LOGGER_LEVEL CLogger::ELevel::INFO
#endif//SYS_LOGGER_INFO
#ifdef SYS_LOGGER_WARN
#  define SYS_LOGGER_LEVEL CLogger::ELevel::WARN
#endif//SYS_LOGGER_WARN
#ifdef SYS_LOGGER_ERROR
#  define SYS_LOGGER_LEVEL CLogger::ELevel::ERROR
#endif//SYS_LOGGER_ERROR
#ifdef SYS_LOGGER_FATAL
#  define SYS_LOGGER_LEVEL CLogger::ELevel::ERROR
#endif//SYS_LOGGER_FATAL
#ifdef SYS_LOGGER_NONE
#  define SYS_LOGGER_LEVEL CLogger::ELevel::NONE
#endif//SYS_LOGGER_NONE

#ifdef SYS_LOGGER_COUT
#  define SYS_LOGGER_PROVIDER CCoutLoggerProvider
#endif//SYS_LOGGER_COUT

#ifndef SYS_LOGGER_LEVEL
#  define SYS_LOGGER_LEVEL CLogger::ELevel::DEBUG
#endif//SYS_LOGGER_LEVEL
#ifndef SYS_LOGGER_PROVIDER
#  define SYS_LOGGER_PROVIDER CCoutLoggerProvider
#endif//SYS_LOGGER_PROVIDER

#ifndef SYS_LOGGER
  #define SYS_LOG_NFO(data)
  #define SYS_LOG_DBG(data)
  #define SYS_LOG_WRN(data)
  #define SYS_LOG_ERR(data)
#else
  #define SYS_LOG_NFO(data) sys::log::nfo << data << sys::log::end;
  #define SYS_LOG_DBG(data) sys::log::dbg << data << sys::log::end;
  #define SYS_LOG_WRN(data) sys::log::wrn << data << sys::log::end;
  #define SYS_LOG_ERR(data) sys::log::err << data << sys::log::end;
#endif // SYS_LOGGER 

namespace sys {
#ifdef SYS_LOGGER
  constexpr bool LOGGER {true};
#else // SYS_LOGGER
  constexpr bool LOGGER {false};
#endif//SYS_LOGGER
  
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
  
  class CLogger : public TSingleton<CLogger> {
    public:
      enum class EManipulator: int {
        END = 0x0,
        NL  = 0x1,
        TAB = 0x2,
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
      std::string      mOutput;
      ELevel           mLevel      {SYS_LOGGER_LEVEL};
      CLoggerProvider* mProvider   {nullptr};
      sys::string      mTimeFormat {"%Y-%m-%d %H:%M:%S"};
    public:
      CLogger();
      virtual ~CLogger();
    public: // operators
      template<typename T> CLogger* operator << (const T& output) { return push(output); }
    public: // friends
      friend const CLogger::ELevel& operator <<(const CLogger::ELevel&, const CLogger::EManipulator&);
      template<typename T> friend const CLogger::ELevel& operator <<(const CLogger::ELevel&, const T&);
      friend CLogger* operator <<(CLogger*, const std::string&);
    public:
      template<typename T> CLogger* push(const T& output) {
#if   defined(SYS_LOGGER_DEBUG)
      mLevel = ELevel::DEBUG;
#elif defined(SYS_LOGGER_INFO)
      mLevel = ELevel::INFO;
#elif defined(SYS_LOGGER_WARN)
      mLevel = ELevel::WARN;
#elif defined(SYS_LOGGER_ERROR)
      mLevel = ELevel::ERROR;
#elif defined(SYS_LOGGER_FATAL)
      mLevel = ELevel::ERROR;
#elif defined(SYS_LOGGER_NONE)
      mLevel = ELevel::NONE;
#endif//SYS_LOGGER_NONE
      std::stringstream ss;
      ss << output;
      mOutput.append(ss.str());
      return this;
    }
    public: // get&set
      void   level(ELevel&& eLevel) { mLevel = std::move(eLevel); }
      ELevel level()                { return mLevel; }
      void             provider(CLoggerProvider*&& pProvider) { delete mProvider; mProvider = std::move(pProvider); }
      CLoggerProvider* provider() { if (!mProvider) mProvider = new SYS_LOGGER_PROVIDER; return mProvider; }
  };
  
  template<typename T> const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const T& output) {
    CLogger::getSingleton()->push(output);
    return type;
  }
  
  using log = CLogger;
}

#endif //__clogger_hpp__
