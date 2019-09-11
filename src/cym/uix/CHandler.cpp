#include "cym/uix/CHandler.hpp"

namespace cym { namespace uix {
  CHandler::CHandler() {
    log::dbg << "uix::CHandler::CHandler()::" << this << log::end;
  }
  
  CHandler::~CHandler() {
    log::dbg << "uix::CHandler::~CHandler()::" << this << log::end;
  }
}}
