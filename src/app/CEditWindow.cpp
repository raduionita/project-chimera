#include "app/CEditWindow.hpp"
#include "uix/CPanel.hpp"
#include "uix/CButton.hpp"
#include "uix/CLayout.hpp"
#include "uix/CPainter.hpp"
#include "uix/CEvent.hpp"
#include "uix/CFrame.hpp"
#include "uix/CSurface.hpp"

#include <cym/CBuffer.hpp>
#include <cym/CVertexArray.hpp>
#include <cym/CLayout.hpp>
#include <cym/CShader.hpp>

namespace app {
  CEditWindow::CEditWindow() : uix::CToplevel(uix::CToplevel::WINDOW) {
    log::nfo << "app::CEditWindow::CEditWindow()::" << this << log::end;
  }
  
  CEditWindow::~CEditWindow() {
    log::nfo << "app::CEditWindow::~CEditWindow()::" << this << log::end;
  }
  
  void CEditWindow::onInit() {
    log::nfo << "app::CEditWindow::onInit()::" << this << log::end;
  }
  
  void CEditWindow::onFree() {
    log::nfo << "app::CEditWindow::onFree()::" << this << log::end;
  }
}
