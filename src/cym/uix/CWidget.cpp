#include "cym/uix/CWidget.hpp"

namespace cym { namespace uix { 
  CWidget::~CWidget() {
    std::cout << "uix::CWidget::~CWidget()::" << this << std::endl;
  }
}}


// @todo: on default size draw widget using parent inner size
