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
    CYM_LOG_NFO("app::CEditWindow::CEditWindow()::" << this);
  }
  
  CEditWindow::~CEditWindow() {
    CYM_LOG_NFO("app::CEditWindow::~CEditWindow()::" << this);
  }
  
  void CEditWindow::onInit() {
    CYM_LOG_NFO("app::CEditWindow::onInit()::" << this);
  }
  
  void CEditWindow::onFree() {
    CYM_LOG_NFO("app::CEditWindow::onFree()::" << this);
  }
}
