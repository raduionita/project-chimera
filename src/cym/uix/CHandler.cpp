#include "cym/uix/CHandler.hpp"

namespace cym { namespace uix {
  CHandler::CHandler() {
    std::cout << "uix::CHandler::CHandler()::" << this << std::endl;
  }
  
  CHandler::~CHandler() {
    std::cout << "uix::CHandler::~CHandler()::" << this << std::endl;
  }
}}
