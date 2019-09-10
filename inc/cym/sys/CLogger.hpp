#ifndef __cym_sys_clogger_hpp__
#define __cym_sys_clogger_hpp__

#include "sys.hpp"
#include "CSingleton.hpp"

#include <memory>

#define LOGGING_DEBUG CLogger::ELevel::DEBUG
#define LOGGING_INFO  CLogger::ELevel::INFO
#define LOGGING_WARN  CLogger::ELevel::WARN
#define LOGGING_ERROR CLogger::ELevel::ERROR
#define LOGGING_FATAL LOGGING_ERROR

#ifndef LOGGING
#  define LOGGING 0
#endif//LOGGING
#ifndef LOGGING_LEVEL
#  define LOGGING_LEVEL LOGGING_ERROR
#endif//LOGGING_LEVEL
#ifndef LOGGING_PROVIDER
#  define LOGGING_PROVIDER CCoutLoggerProvider
#endif//LOGGING_STRATEGY

namespace cym { namespace sys {
  class CLogger : public CSingleton<CLogger> {
    public:
      class CProvider {
          friend class CLogger;
        public:
          CProvider();
          virtual ~CProvider();
        public:
          virtual void log(const std::string& message) = 0;
      };
    public:
      enum class EManipulator: int {
        END = 0x0,
      };
      enum class ELevel      : int {
        FATAL = 1,
        ERROR = FATAL,
        WARN  = 2 | ERROR,
        INFO  = 4 | WARN,
        DEBUG = 8 | INFO,
      };
    public:
      static const ELevel       nfo;
      static const ELevel       dbg;
      static const ELevel       wrn;
      static const ELevel       err;
      static const EManipulator end;
    protected:  
      ELevel      mLevel    = {LOGGING_LEVEL};
      std::string mOutput;
      CProvider*  mProvider = {nullptr};
    public:
      CLogger();
      virtual ~CLogger();
    public:
      template <typename T> CLogger* operator << (const T& output) {
        return push(output);
      }
      
      friend const CLogger::ELevel& operator <<(const CLogger::ELevel&, const CLogger::EManipulator&);
      
      template <typename T> friend const CLogger::ELevel& operator <<(const CLogger::ELevel&, const T&);
      
      friend CLogger* operator <<(CLogger*, ELevel);
      
      friend CLogger* operator <<(CLogger*, const std::string&);
    protected:
      template <typename T> CLogger* push(const T& output) {
        std::stringstream ss;
        ss << output;
        mOutput.append(ss.str());
        return this;
      }
  };
  
  class CFileLoggerProvider : public CLogger::CProvider {
    public:
      virtual void log(const std::string&);
  };
  
  class CCoutLoggerProvider: public CLogger::CProvider {
    public:
      virtual void log(const std::string&);
  };
  
  template <typename T> const CLogger::ELevel& operator <<(const CLogger::ELevel& type, const T& output) {
    CLogger::instance()->push(output);
    return type;
  }
}}

#endif //__cym_sys_clogger_hpp__
