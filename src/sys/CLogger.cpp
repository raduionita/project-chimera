#include "sys/CLogger.hpp"

#include <cstring>

namespace sys {
  const CLogger::ELevel       CLogger::dbg{ELevel::DEBUG};
  const CLogger::ELevel       CLogger::nfo{ELevel::INFO};
  const CLogger::ELevel       CLogger::wrn{ELevel::WARN};
  const CLogger::ELevel       CLogger::err{ELevel::ERROR};
  const CLogger::EManipulator CLogger::end{EManipulator::END};
  
  CLogger::CLogger() { }
  
  CLogger::~CLogger() {
    delete mProvider; 
  }
  
  CLoggerProvider::CLoggerProvider() { }
  
  CLoggerProvider::~CLoggerProvider() { }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const CLogger::ELevel& operator <<(const CLogger::ELevel& eLevel, const CLogger::EManipulator& eManipulator) {
    static auto& sLogger {CLogger::getSingleton()};
    // emptyness guard
    if (sLogger.mOutput.empty())
      return eLevel;
    // logging level matches
    if (int(eLevel) <= int(sLogger.level())) {
      // prefix
      time_t nTime  = std::time(nullptr);
      auto   oLocal = std::localtime(&nTime);
      //->[2019-12-02 17:19:34] [NFO] <-
      //->[12:08:17] [NFO] <-
// @TODO use sLogger->mTimeFormat.size();
      char zPrefix[18]; zPrefix[17] = '\0';
      std::strftime(zPrefix, 18, "[%H:%M:%S] [XXX] ", oLocal); // 
      // level
      switch(eLevel) {
        default:
        case CLogger::ELevel::DEBUG: ::strncpy(&zPrefix[11],"[DBG] ",6); break;
        case CLogger::ELevel::INFO : ::strncpy(&zPrefix[11],"[NFO] ",6); break;
        case CLogger::ELevel::WARN : ::strncpy(&zPrefix[11],"[WRN] ",6); break;
        case CLogger::ELevel::FATAL: ::strncpy(&zPrefix[11],"[ERR] ",6); break;
      }
      // end the stream
      switch (eManipulator) {
        default: break;
        case CLogger::EManipulator::NL: {
          sLogger.mOutput.append("\n");
          break;
        }
        case CLogger::EManipulator::END: {
          std::stringstream stream;
          std::string&      output = sLogger.mOutput; 
          stream << output;
          output.clear();
          std::string line;
          for (int i = 0; std::getline(stream, line); i++) {
            if (i == 0) 
              output.append(zPrefix);
            else
              output.append("                            ");
            output.append(line).append("\n");
          }
          sLogger.provider()->log(output);
          break;
        }
      }
    }
    // clear output
    sLogger.mOutput.clear();
    // chaining
    return eLevel;
  }
    
  CLogger& operator <<(CLogger&, const std::string& output) {
    return CLogger::push(output);
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CCoutLoggerProvider::log(const std::string& output) {
    std::cout << output;
  }
  
  void CFileLoggerProvider::log(const std::string& output) {
    
  }
}
