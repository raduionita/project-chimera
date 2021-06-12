#ifndef __sys_clogger_hpp__
#define __sys_clogger_hpp__

#include "sys/sys.hpp"
#include "sys/CSingleton.hpp"

#include <memory>

#ifndef CYM_LOGGER
  // no logging
#endif//CYM_LOGGER

#ifdef CYM_LOGGER_DEBUG
#  define CYM_LOGGER_LEVEL CLogger::ELevel::DEBUG
#endif//CYM_LOGGER_DEBUG
#ifdef CYM_LOGGER_INFO
#  define CYM_LOGGER_LEVEL CLogger::ELevel::INFO
#endif//CYM_LOGGER_INFO
#ifdef CYM_LOGGER_WARN
#  define CYM_LOGGER_LEVEL CLogger::ELevel::WARN
#endif//CYM_LOGGER_WARN
#ifdef CYM_LOGGER_ERROR
#  define CYM_LOGGER_LEVEL CLogger::ELevel::ERROR
#endif//CYM_LOGGER_ERROR
#ifdef CYM_LOGGER_FATAL
#  define CYM_LOGGER_LEVEL CLogger::ELevel::ERROR
#endif//CYM_LOGGER_FATAL
#ifdef CYM_LOGGER_NONE
#  define CYM_LOGGER_LEVEL CLogger::ELevel::NONE
#endif//CYM_LOGGER_NONE

#ifdef CYM_LOGGER_COUT
#  define CYM_LOGGER_PROVIDER CCoutLoggerProvider
#endif//CYM_LOGGER_COUT

#ifndef CYM_LOGGER_LEVEL
#  define CYM_LOGGER_LEVEL CLogger::ELevel::DEBUG
#endif//CYM_LOGGER_LEVEL
#ifndef CYM_LOGGER_PROVIDER
#  define CYM_LOGGER_PROVIDER CCoutLoggerProvider
#endif//CYM_LOGGER_PROVIDER

#ifndef CYM_LOGGER
  #define CYM_LOG_NFO(data)
  #define CYM_LOG_DBG(data)
  #define CYM_LOG_WRN(data)
  #define CYM_LOG_ERR(data)
#else
  #define CYM_LOG_NFO(data) sys::log::nfo << data << sys::log::end;
  #define CYM_LOG_DBG(data) sys::log::dbg << data << sys::log::end;
  #define CYM_LOG_WRN(data) sys::log::wrn << data << sys::log::end;
  #define CYM_LOG_ERR(data) sys::log::err << data << sys::log::end;
#endif // CYM_LOGGER 

namespace sys {
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
      ELevel           mLevel    {CYM_LOGGER_LEVEL};
      CLoggerProvider* mProvider {nullptr};
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
  
  template<typename T> const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const T& output) {
    CLogger::getSingleton()->push(output);
    return type;
  }
  
  using log = CLogger;
}

#endif //__clogger_hpp__
