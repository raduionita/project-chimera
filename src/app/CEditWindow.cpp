#include "app/CEditWindow.hpp"
#include "uix/CPanel.hpp"
#include "uix/CButton.hpp"
#include "uix/CLayout.hpp"
#include "uix/CPainter.hpp"
#include "uix/CEvent.hpp"
#include "uix/CFrame.hpp"
#include "uix/CSurface.hpp"

#include <cym/CDataBuffer.hpp>
#include <cym/CVertexArray.hpp>
#include <cym/CVertexLayout.hpp>
#include <cym/CShader.hpp>

namespace app {
  CEditWindow::CEditWindow() : uix::CFrame(uix::CFrame::WINDOW) {
    SYS_LOG_NFO("app::CEditWindow::CEditWindow()::" << this);
  }
  
  CEditWindow::~CEditWindow() {
    SYS_LOG_NFO("app::CEditWindow::~CEditWindow()::" << this);
  }
  
  void CEditWindow::onInit() {
    SYS_LOG_NFO("app::CEditWindow::onInit()::" << this);
  }
  
  void CEditWindow::onFree() {
    SYS_LOG_NFO("app::CEditWindow::onFree()::" << this);
  }
}
