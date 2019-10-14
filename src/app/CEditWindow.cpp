#include "app/CEditWindow.hpp"
#include "uix/CPanel.hpp"
#include "uix/CButton.hpp"
#include "uix/CLayout.hpp"
#include "uix/CPainter.hpp"
#include "uix/CEvent.hpp"
#include "uix/CFrame.hpp"
#include "uix/CSurface.hpp"

namespace app {
  void CEditWindow::onInit() {
    log::dbg << "app::CEditWindow::onInit()::" << this << log::end;
         
    auto pLayout  = this->layout(new uix::CBoxLayout(uix::ELayout::VERTICAL));
         mSurface = pLayout->add(new uix::CSurface(this, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pPanel   = pLayout->add(new uix::CPanel(this, uix::EWindow::VISIBLE), uix::ELayout::ADJUST);
    auto pButton  = new uix::CButton(pPanel, "RESIZE", {50,50,90,40});
  
    pPanel->style()->background(uix::SColor{33,33,33});
    
    attach(this,    uix::EEvent::KEYDOWN,     &app::CEditWindow::onKeydown);
    attach(pPanel,  uix::EEvent::DRAW,        &app::CEditWindow::onDraw);
    attach(pPanel,  uix::EEvent::COMMAND,     &app::CEditWindow::onCommand);
    attach(pButton, uix::EEvent::LBUTTONDOWN, &app::CEditWindow::onClick);
    attach(mSurface,uix::EEvent::RESIZE,      &uix::CRender::onResize);
    
    this->layout(pLayout);
    this->title(mSurface->version());
    this->show();
  }
  
  void CEditWindow::onFree() {
    log::dbg << "app::CEditWindow::onFree()::" << this << log::end;
  }
  
  void CEditWindow::onKeydown(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onKeydown(CEvent*)::" << this << " K:" << pEvent->key() << log::end;
    
    switch (pEvent->key()) {
      case 'Q'      : close(); break;
      case VK_ESCAPE: close(); break;
      case VK_F5    : mSurface->reset(); break;
      case VK_F11   : fullscreen(); break;
    }
  }
  
  void CEditWindow::onClick(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onClick(CEvent*)::" << this << " B:" << int(pEvent->button()) << " X:" << pEvent->clientX() << " Y:" << pEvent->clientY() << log::end;
  
    mSurface->area({0, 0, 100, 100});
    close();
  }
  
  void CEditWindow::onCommand(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onCommand(CEvent*)::" << this << " S:" << int(pEvent->state()) << log::end;
  }
  
  void CEditWindow::onDraw(uix::CEvent* pEvent) {
    log::nfo << "app::CEditWindow::onDraw(CEvent*)::" << this << log::end;
    
    uix::CPainter oPainter(pEvent->target());
    
    oPainter.rectangle({0,0,10,30});
  }
}
