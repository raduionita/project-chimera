#include "cym/sys/CLogger.hpp"

namespace cym { namespace sys {
  const CLogger::ELevel       CLogger::dbg{ELevel::DEBUG};
  const CLogger::ELevel       CLogger::nfo{ELevel::INFO};
  const CLogger::ELevel       CLogger::wrn{ELevel::WARN};
  const CLogger::ELevel       CLogger::err{ELevel::ERROR};
  const CLogger::EManipulator CLogger::end{EManipulator::END};
  
  CLogger::CLogger() { mProvider = new LOGGING_PROVIDER; }
  
  CLogger::~CLogger() { delete mProvider; mProvider = nullptr; }
  
  CLogger::CProvider::CProvider() { }
  
  CLogger::CProvider::~CProvider() { }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const CLogger::ELevel& operator <<(const CLogger::ELevel& eLevel, const CLogger::EManipulator& eManipulator) {
    auto sLogger = CLogger::instance();
    
    if (!sLogger->mOutput.empty()) {
      // logging level matches
      if (1 || int(eLevel) <= int(sLogger->mLevel)) {
        switch(eLevel) {
          default:
          case CLogger::ELevel::DEBUG: sLogger->mOutput = "[DBG] " + sLogger->mOutput; break;
          case CLogger::ELevel::INFO : sLogger->mOutput = "[NFO] " + sLogger->mOutput; break;
          case CLogger::ELevel::WARN : sLogger->mOutput = "[WRN] " + sLogger->mOutput; break;
          case CLogger::ELevel::FATAL: sLogger->mOutput = "[ERR] " + sLogger->mOutput; break;
        }
  
        time_t nTime  = std::time(nullptr);
        auto   sLocal = std::localtime(&nTime);
  
        char szTime[23];
        std::strftime(szTime, 23, "[%Y-%m-%d %H:%M:%S] ", sLocal);
        szTime[22] = '\0';
  
        sLogger->mOutput = szTime + sLogger->mOutput;
  
        switch (eManipulator) {
          case CLogger::EManipulator::END: {
            sLogger->mOutput.append("\n");
            sLogger->mProvider->log(sLogger->mOutput);
          }
          default:/*do nothing*/break;
        }
      }
      // clear output
      sLogger->mOutput.clear();
    }
    
    return eLevel;
  }
  
  CLogger* operator <<(CLogger*, CLogger::ELevel type) {
    return CLogger::instance();
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
