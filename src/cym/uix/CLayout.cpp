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
  
  template <typename T> CLayout::TItem<T>::TItem(T item, int hints/*=0*/) : BItem(hints), mItem(item) {}
  
  template <typename T> CObject* CLayout::TItem<T>::operator ->() { return mItem; }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> bool CLayout::TItem<T>::area(const SArea& sArea) {
    log::nfo << "uix::CLayout::TItem<T>::area(SArea&)" << log::end;
    mArea = sArea;
    // require recalculation for the child
    return calc();
  }
  
  template <typename T> bool CLayout::TItem<T>::calc() {
    log::nfo << "uix::CLayout::TItem<T>::calc()" << log::end;
    
    auto  sArea = mItem->area(); // cur child (window/layout)
    
    // win.area.xy = itm.area.xy + ...
    sArea.x = mArea.x + ((mHints & ELayout::ADJUST) || (mHints & ELayout::LEFT) ? 0 // 0 = don't add anyting // if ADJUST or LEFT 
                                                                            : ((mHints & ELayout::RIGHT)  ? (mArea.w - sArea.w) // itm.w - win.w = where x should be // if RIGHT
                                                                                                        : ((mHints & ELayout::CENTER) ? ((mArea.w - sArea.w)/2) // mid x = half itm.w - half wnd.x //
                                                                                                                                    : (sArea.x)))); // wnd.x pos inside itm
    sArea.y = mArea.y + ((mHints & ELayout::ADJUST) || (mHints & ELayout::TOP)  ? 0
                                                                            : ((mHints & ELayout::BOTTOM) ? (mArea.h - sArea.h) 
                                                                                                        : ((mHints & ELayout::CENTER) ? ((mArea.h - sArea.h)/2)
                                                                                                                                    : (sArea.y))));
    // win.area.wh = itm.area.wh OR same
    sArea.w = (mHints & ELayout::ADJUST) ? mArea.w : sArea.w;
    sArea.h = (mHints & ELayout::ADJUST) ? mArea.h : sArea.h; 
    
    return mItem->area({std::max(0, sArea.x), std::max(0, sArea.y), sArea.w, sArea.h}); 
  }
  
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
  
  CWindow* CBoxLayout::add(CWindow* pItem, const ELayout& eLayout/*=ELayout::EMPTY*/) {
    return add(pItem, int(eLayout));
  }
  
  CWindow* CBoxLayout::add(CWindow* pItem, int nHints/*=0*/) {
    log::nfo << "uix::CBoxLayout::add(CWindow*, hints)::" << this << log::end;
    
    mItems.push_back(new TItem<CWindow*>(pItem,nHints));
    // @todo: do I need to do something here...like resizing or something?!
    
    return pItem;
  }
  
  CLayout* CBoxLayout::add(CLayout* pItem, const ELayout& eLayout/*=ELayout::EMPTY*/) {
    return add(pItem, int(eLayout));
  }
  
  CLayout* CBoxLayout::add(CLayout* pItem, int nHints/*=0*/) {
    log::nfo << "uix::CBoxLayout::add(CLayout*, hints)::" << this << log::end;
    
    mItems.push_back(new TItem<CLayout*>(pItem,nHints));
    // @todo: do I need to do something here...like resizing or something?!
    
    return pItem;
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
