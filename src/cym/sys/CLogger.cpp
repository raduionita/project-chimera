#include "cym/sys/CLogger.hpp"

namespace cym { namespace sys {
  const CLogger::EType        CLogger::dbg{EType::DEBUG};
  const CLogger::EType        CLogger::nfo{EType::INFO};
  const CLogger::EType        CLogger::wrn{EType::WARN};
  const CLogger::EType        CLogger::err{EType::ERROR};
  const CLogger::EManipulator CLogger::end{EManipulator::END};
  
  CLogger::CLogger() { mProvider = new LOGGING_PROVIDER; }
  
  CLogger::~CLogger() { delete mProvider; mProvider = nullptr; }
  
  CLogger::CProvider::CProvider() { }
  
  CLogger::CProvider::~CProvider() { }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const CLogger::EType& operator <<(const CLogger::EType& type, const CLogger::EManipulator& manipulator) {
    auto sLogger = CLogger::instance();
    
    if (!sLogger->mOutput.empty()) {
      switch(sLogger->mType) {
        default:
        case CLogger::EType::DEBUG: sLogger->mOutput = "[DBG] " + sLogger->mOutput; break;
        case CLogger::EType::INFO : sLogger->mOutput = "[NFO] " + sLogger->mOutput; break;
        case CLogger::EType::WARN : sLogger->mOutput = "[WRN] " + sLogger->mOutput; break;
        case CLogger::EType::FATAL: sLogger->mOutput = "[ERR] " + sLogger->mOutput; break;
      }
      
      time_t nTime  = std::time(nullptr);
      auto   sLocal = std::localtime(&nTime);
      
      char szTime[23];
      std::strftime(szTime, 23, "[%Y-%m-%d %H:%M:%S] ", sLocal);
      szTime[22] = '\0';
      
      sLogger->mOutput = szTime + sLogger->mOutput;
      
      switch (manipulator) {
        case CLogger::EManipulator::END: {
          sLogger->mOutput.append("\n");
          sLogger->mProvider->log(sLogger->mOutput);
          sLogger->mOutput.clear();
        }
        default:/*do nothing*/break;
      }
    }
    
    return type;
  }
  
  CLogger* operator <<(CLogger*, CLogger::EType type) {
    return CLogger::instance()->type(type);
  }
  
  CLogger* operator <<(CLogger*, const std::string& output) {
    return CLogger::instance()->push(output);
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CCoutLoggerProvider::log(const std::string& output) {
    std::cout << output;
  }
  
  void CFileLoggerProvider::log(const std::string& output) {
    
  }
}}
