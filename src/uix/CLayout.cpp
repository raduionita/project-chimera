#include "uix/CLayout.hpp"
#include "uix/CWindow.hpp"

namespace uix {
  bool CLayout::apply(CWindow* pWindow) {
    CYM_LOG_NFO("uix::CLayout::getLayout(CWindow*)::" << this);
    
    RETURN(!(pWindow->mState & EState::INITED), false);
    
    (pWindow != nullptr) && (mWindow = pWindow);
    mArea   = mWindow->area();
    mArea.x = AUTO;
    mArea.y = AUTO;
    return area(mArea);
  }
  
  bool CLayout::area(const SArea& sArea) {
    CYM_LOG_NFO("uix::CLayout::area(SArea&)::" << this);
    mArea = sArea;
    
    for (auto pChild : mWindow->children()) {
      //pChild->size(AUTO,AUTO);
      auto pLayout = pChild->layout();
      if (pLayout) {
        pLayout->apply(pChild);
      }
    }
    
    return true;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  CLayout::CItem::CItem(int hints/*=0*/, const SArea& tArea/*={0}*/) : mHints{hints}, mArea{tArea} {}
   
  CLayout::CItem::~CItem() {}
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CLayout::CItem* CBoxLayout::item(typename decltype(mItems)::size_type i) {
    assert((i < mItems.size()) && "CBoxLayout::item(i) can't reach that element!");
    return mItems[i];
  }
    
  CWindow* CBoxLayout::add(CWindow* pWindow, const ELayout& eLayout/*=ELayout::LAYOUT*/) {
    CYM_LOG_NFO("uix::CBoxLayout::add(CWindow*,int)::" << this);
    auto tLayout = eLayout | (pWindow->hint(EWindow::AUTOWH) ? ELayout::ADJUST : ELayout::LAYOUT);
    mItems.push_back(std::move(new TItem<CWindow>{pWindow, tLayout, pWindow->area()}));
    return pWindow;
  }
  
  CLayout* CBoxLayout::add(CLayout* pLayout, const ELayout& eLayout/*=ELayout::LAYOUT*/) {
    CYM_LOG_NFO("uix::CBoxLayout::add(CLayout*,int)::" << this);
    auto tLayout = pLayout->hints() | eLayout | (pLayout->area() == AUTO ? ELayout::ADJUST : ELayout::LAYOUT);
    mItems.push_back(std::move(new TItem<CLayout>{pLayout, tLayout, pLayout->area()}));
    return pLayout;
  }
  
  bool CBoxLayout::area(const SArea& sArea) {
    CYM_LOG_NFO("uix::CBoxLayout::area(SArea&)::" << this << " DIR:0b" << std::bitset<32>(int(mHints)) << " COUNT:" << mItems.size());
  
    RETURN(!mItems.size(),false);
    
    mArea = sArea;
    
    int nItems = (int)(mItems.size());
    
    if (nItems == 0) {
      return false;
    }
    
    if (mHints & ELayout::HORIZONTAL) {
      int nFixW  = 0;
      int nAdhW  = 0;
      int nCntF  = 0;
      int iItem  = 0;
      // for each item
      for (iItem = 0; iItem < nItems; iItem++) {
        CItem*& pItem = mItems[iItem];
        if (~(pItem->hints()) & ELayout::ADJUST) { // fixed value
          nFixW += pItem->area().w;
          nCntF++;
        }
      }
      int nCntA = nItems - nCntF;
      int nAdjW = mArea.w - nFixW;
      int nAvgW = nCntA != 0 ? (nAdjW / nCntA) : 0;
      int nModW = nCntA != 0 ? (nAdjW % nCntA) : 0; // remaining pixels h
      int nOffX = 0;
      int nOffY = mArea.y == AUTO ? 0 : mArea.y;
      int nNewW = 0;
      int nNewH = mArea.h;
      // for each item
      for (iItem = 0; iItem < nItems; iItem++) {
        CItem*& pItem = mItems[iItem];
        // y: move item starting w/ current 
        if (pItem->hints() & ELayout::ADJUST) {
          // add remaining px to width, 1 by 1 to each item 
          nNewW = nAvgW + (--nModW >= 0 ? 1 : 0);
        } else {
          nNewW = pItem->area().w; // here seme as pItem->mObject->area().w
        }
        // x: move item starting w/ current offset // y:same // w:resized // h:same
        pItem->area({nOffX, nOffY, nNewW, nNewH}); // this sets the CLayout::TItem not it's attach
        // offset width by new width
        nOffX += nNewW;
      }
    } else { // mHints & ELayout::VERTICAL // default
      int nFixH  = 0;
      int nAdhH  = 0;
      int nCntF  = 0;
      int iItem  = 0;
      // for each item
      for (iItem = 0; iItem < nItems; iItem++) {
        CItem*& pItem = mItems[iItem];
        if (~(pItem->hints()) & ELayout::ADJUST) { // fixed value
          nFixH += pItem->area().h;
          nCntF++;
        }
      }
      int nCntA = nItems - nCntF;
      int nAdjH = mArea.h - nFixH;
      int nAvgH = nCntA != 0 ? (nAdjH / nCntA) : 0;
      int nModH = nCntA != 0 ? (nAdjH % nCntA) : 0; // remaining pixels h
      int nOffY = 0;
      int nOffX = mArea.x == AUTO ? 0 : mArea.x;
      int nNewH = 0;
      int nNewW = mArea.w;
      // for each item
      for (iItem = 0; iItem < nItems; iItem++) {
        CItem*& pItem = mItems[iItem];
        // x: move item starting w/ current 
        if (pItem->hints() & ELayout::ADJUST) {
          // add remaining px to height, 1 by 1 to each item
          nNewH = nAvgH + (--nModH >= 0 ? 1 : 0);
        } else {
          nNewH = pItem->area().h;
        }
        pItem->area({nOffX, nOffY, nNewW, nNewH}); // this sets the CLayout::TItem not it's attach
        // offset height by new height
        nOffY += nNewH;
      }
    }
    
    return true;
  }
}
