#include "cym/uix/CLayout.hpp"
#include "cym/uix/CWindow.hpp"

namespace cym { namespace uix {
  CLayout::CLayout(CWindow* pWindow/*=nullptr*/) : mWindow{pWindow} {
    log::nfo << "uix::CLayout::CLayout(CWindow*)::" << this << log::end;
  }
  
  CLayout::~CLayout() {
    log::nfo << "uix::CLayout::~CLayout()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CLayout::layout(CWindow* pWindow) {
    log::nfo << "uix::CLayout::layout(CWindow*)::" << this << log::end;
    mWindow  = pWindow;
    mArea    = mWindow->area();
    return calc();
  }
  
  SArea CLayout::area() const {
    log::nfo << "uix::CLayout::area()::" << this << log::end;
    return mArea;
  }
  
  bool CLayout::area(const SArea& sArea) {
    log::nfo << "uix::CLayout::area(SArea&)::" << this << log::end;
    mArea = sArea;
    return calc();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  CLayout::BItem::BItem(int hints/*=0*/) : mHints(hints) {}
   
  CLayout::BItem::~BItem() {}
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CBoxLayout::CBoxLayout(CWindow* pWindow/*=nullptr*/, ELayout eDirection/*ELayout::VERTICAL*/) : CLayout(pWindow), mDirection{eDirection} {
    log::nfo << "uix::CBoxLayout::CBoxLayout(CWindow*,ELayout)::" << this << log::end;
  }
  
  CBoxLayout::CBoxLayout(ELayout eDirection) : CLayout(nullptr), mDirection{eDirection} {
    log::nfo << "uix::CBoxLayout::CBoxLayout(ELayout)::" << this << log::end;
  }
  
  CBoxLayout::~CBoxLayout() {
    log::nfo << "uix::CBoxLayout::~CBoxLayout()::" << this << log::end;
  }
  
  CLayout::BItem* CBoxLayout::operator[](typename decltype(mItems)::size_type i) {
    assert((i < mItems.size()) && "CBoxLayout::operator[i] can't reach that element!");
    return mItems[i];
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CLayout::BItem* CBoxLayout::item(typename decltype(mItems)::size_type i) {
    assert((i < mItems.size()) && "CBoxLayout::item(i) can't reach that element!");
    return mItems[i];
  }
  
  bool CBoxLayout::calc() {
    log::nfo << "uix::CBoxLayout::calc()::" << this << " DIR:0b" << std::bitset<32>(int(mDirection)) << " COUNT:" << mItems.size() << log::end;
    
    RETURN(!mItems.size(),false);
    
    int nItems = (int)(mItems.size());
    
    int nItemW = (int)(mArea.w / nItems); // item w
    int nItemH = (int)(mArea.h / nItems); // item h
    int nModW  = (int)(mArea.w % nItems); // remaining pixels w
    int nModH  = (int)(mArea.h % nItems); // remaining pixels h
    
    if (mDirection == ELayout::HORIZONTAL) {
      // total (offset) w so far
      int nOffW = 0;
      // for each item
      for (int i = 0; i < nItems; i++) {
        BItem*& pItem = mItems[i];
        // add remaining px to width, 1 by 1 to each item 
        int     nAdjW = --nModW >= 0 ? 1 : 0;
        // x: move item starting w/ current offset // y:same // w:resized // h:same
        pItem->area({nOffW, mArea.y, nItemW + nAdjW, mArea.h}); // this sets the CLayout::TItem not it's child
        // offset width by new width
        nOffW += nItemW + nAdjW;
      }
    } else { // mDirection == ELayout::VERTICAL // default
      int nOffH = 0;
      for (int i = 0; i < nItems; i++) {
        BItem*& pItem = mItems[i];
        // add remaining px to height, 1 by 1 to each item
        int     nAdjH = --nModH >= 0 ? 1 : 0;
        // x: move item starting w/ current 
        pItem->area({mArea.x, nOffH, mArea.w, nItemH + nAdjH}); // this sets the CLayout::TItem not it's child
        // offset height by new height
        nOffH += nItemH + nAdjH;
      }
    }
    
    return true;
  }
}}
