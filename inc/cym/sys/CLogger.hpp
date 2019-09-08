#ifndef __cym_sys_clogger_hpp__
#define __cym_sys_clogger_hpp__

#include "sys.hpp"
#include "CSingleton.hpp"

#include <memory>

#ifndef LOGGING
#  define LOGGING 0
#endif//LOGGING
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
      enum class EType       : int {
        INFO  = 0x01,
        DEBUG = 0x02,
        WARN  = 0x04,
        FATAL = 0x10,
        ERROR = FATAL,
      };
    public:
      static const EType        nfo;
      static const EType        dbg;
      static const EType        wrn;
      static const EType        err;
      static const EManipulator end;
    protected:  
      EType           mType     = {EType::DEBUG};
      std::string     mOutput;
      CProvider*      mProvider = {nullptr};
    public:
      CLogger();
      virtual ~CLogger();
    public:
      CLogger& operator << (EType type) {
        mType = type;
        return *this;
      }
      
      template <typename T> CLogger* operator << (const T& output) {
        return push(output);
      }
      
      friend const CLogger::EType& operator <<(const CLogger::EType&, const CLogger::EManipulator&);
      
      template <typename T> friend const CLogger::EType& operator <<(const CLogger::EType&, const T&);
      
      friend CLogger* operator <<(CLogger*, EType);
      
      friend CLogger* operator <<(CLogger*, const std::string&);
    protected:
      template <typename T> CLogger* push(const T& output) {
        std::stringstream ss;
        ss << output;
        mOutput.append(ss.str());
        return this;
      }
      
      CLogger* type(EType type) { mType = type; return this; }
  };
  
  class CFileLoggerProvider : public CLogger::CProvider {
    public:
      virtual void log(const std::string&);
  };
  
  class CCoutLoggerProvider: public CLogger::CProvider {
    public:
      virtual void log(const std::string&);
  };
  
  template <typename T> const CLogger::EType& operator <<(const CLogger::EType& type, const T& output) {
    CLogger::instance()->type(type)->push(output);
    return type;
  }
}}


#endif //__cym_sys_clogger_hpp__
