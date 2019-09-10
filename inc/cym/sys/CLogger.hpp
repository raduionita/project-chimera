#ifndef __cym_sys_clogger_hpp__
#define __cym_sys_clogger_hpp__

#include "sys.hpp"
#include "CSingleton.hpp"

#include <memory>

#define LOGGING_DEBUG dbg
#define LOGGING_INFO  nfo
#define LOGGING_WARN  wrn
#define LOGGING_ERROR err
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
        DEBUG = 0x01,
        INFO  = 0x02,
        WARN  = 0x04,
        FATAL = 0x10,
        ERROR = FATAL,
      };
    public:
      static const ELevel       nfo;
      static const ELevel       dbg;
      static const ELevel       wrn;
      static const ELevel       err;
      static const EManipulator end;
    protected:  
      ELevel          mLevel    = {ELevel::DEBUG};
      std::string     mOutput;
      CProvider*      mProvider = {nullptr};
    public:
      CLogger();
      virtual ~CLogger();
    public:
      CLogger& operator << (ELevel type) {
        mLevel = type;
        return *this;
      }
      
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
      
      CLogger* type(ELevel type) { mLevel = type; return this; }
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
    CLogger::instance()->type(type)->push(output);
    return type;
  }
}}


#endif //__cym_sys_clogger_hpp__
