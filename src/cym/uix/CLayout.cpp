#include "cym/uix/CLayout.hpp"
#include "cym/uix/CWindow.hpp"

namespace cym { namespace uix {
  CLayout::CLayout(CWindow* pWindow/*=nullptr*/) : mWindow{pWindow} {
    std::cout << "uix::CLayout::CLayout(CWindow*)::" << this << std::endl;
  }
  
  CLayout::~CLayout() {
    std::cout << "uix::CLayout::~CLayout()::" << this << std::endl;
  }
  
  bool CLayout::layout(CWindow* pWindow) {
    std::cout << "uix::CLayout::layout(CWindow*)::" << this << std::endl;
    mWindow  = pWindow;
    mArea    = mWindow->area();
    return calc();
  }
  
  SArea CLayout::area() const {
    std::cout << "uix::CLayout::area()::" << this << std::endl;
    return mArea;
  }
  
  bool CLayout::area(const SArea& sArea) {
    std::cout << "uix::CLayout::area(SArea&)::" << this << std::endl;
    mArea = sArea;
    return calc();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  CLayout::BItem::BItem(int hints/*=0*/) : mHints(hints) {}
   
  CLayout::BItem::~BItem() {}
  
  template <typename T> CLayout::TItem<T>::TItem(T item, int hints/*=0*/) : BItem(hints), mItem(item) {}
  
  template <typename T> CObject* CLayout::TItem<T>::operator ->() { return mItem; }
  
  template <typename T> bool CLayout::TItem<T>::area(const SArea& sArea) {
    std::cout << "uix::CLayout::TItem<T>::area(SArea&)" << std::endl;
    mArea = sArea;
    // require recalculation for the child
    return calc();
  }
  
  template <typename T> bool CLayout::TItem<T>::calc() {
    std::cout << "uix::CLayout::TItem<T>::calc()" << std::endl;
    
    auto  sArea = mItem->area(); // cur child (window/layout)
    
    // win.area.xy = itm.area.xy + ...
    sArea.x = mArea.x + ((mHints & EHint::ADJUST) || (mHints & EHint::LEFT) ? 0 // 0 = don't add anyting // if ADJUST or LEFT 
                                                                            : ((mHints & EHint::RIGHT)  ? (mArea.w - sArea.w) // itm.w - win.w = where x should be // if RIGHT
                                                                                                        : ((mHints & EHint::CENTER) ? ((mArea.w - sArea.w)/2) // mid x = half itm.w - half wnd.x //
                                                                                                                                    : (sArea.x)))); // wnd.x pos inside itm
    sArea.y = mArea.y + ((mHints & EHint::ADJUST) || (mHints & EHint::TOP)  ? 0
                                                                            : ((mHints & EHint::BOTTOM) ? (mArea.h - sArea.h) 
                                                                                                        : ((mHints & EHint::CENTER) ? ((mArea.h - sArea.h)/2)
                                                                                                                                    : (sArea.y))));
    // win.area.wh = itm.area.wh OR same
    sArea.w = (mHints & EHint::ADJUST) ? mArea.w : sArea.w;
    sArea.h = (mHints & EHint::ADJUST) ? mArea.h : sArea.h; 
    
    return mItem->area({std::max(0, sArea.x), std::max(0, sArea.y), sArea.w, sArea.h}); 
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CBoxLayout::CBoxLayout(CWindow* pWindow/*=nullptr*/, EHint eDirection/*EHint::VERTICAL*/) : CLayout(pWindow), mDirection{eDirection} {
    std::cout << "uix::CBoxLayout::CBoxLayout(CWindow*,EHint)::" << this << std::endl;
  }
  
  CBoxLayout::CBoxLayout(EHint eDirection) : CLayout(nullptr), mDirection{eDirection} {
    std::cout << "uix::CBoxLayout::CBoxLayout(EHint)::" << this << std::endl;
  }
  
  CBoxLayout::~CBoxLayout() {
    std::cout << "uix::CBoxLayout::~CBoxLayout()::" << this << std::endl;
  }
  
  CLayout::BItem* CBoxLayout::operator[](typename decltype(mItems)::size_type i) {
    assert((i < mItems.size()) && "CBoxLayout::operator[i] can't reach that element!");
    return mItems[i];
  }
  
  CLayout::BItem* CBoxLayout::item(typename decltype(mItems)::size_type i) {
    assert((i < mItems.size()) && "CBoxLayout::item(i) can't reach that element!");
    return mItems[i];
  }
  
  CWindow* CBoxLayout::add(CWindow* pItem, int nHints/*=0*/) {
    std::cout << "uix::CBoxLayout::add(CWindow*, hints)::" << this << std::endl;
    
    mItems.push_back(new TItem<CWindow*>(pItem,nHints));
    // @todo: do I need to do something here...like resizing or something?!
    
    return pItem;
  }
  
  CLayout* CBoxLayout::add(CLayout* pItem, int nHints/*=0*/) {
    std::cout << "uix::CBoxLayout::add(CLayout*, hints)::" << this << std::endl;
    
    mItems.push_back(new TItem<CLayout*>(pItem,nHints));
    // @todo: do I need to do something here...like resizing or something?!
    
    return pItem;
  }
  
  bool CBoxLayout::calc() {
    std::cout << "uix::CBoxLayout::calc()::" << this << " DIR:0b" << std::bitset<32>(mDirection) << " COUNT:" << mItems.size() << std::endl;
    
    RETURN(!mItems.size(),false);
    
    int nItems = (int)(mItems.size());
    
    int nItemW = (int)(mArea.w / nItems); // item w
    int nItemH = (int)(mArea.h / nItems); // item h
    int nModW  = (int)(mArea.w % nItems); // remaining pixels w
    int nModH  = (int)(mArea.h % nItems); // remaining pixels h
    
    if (mDirection == EHint::HORIZONTAL) {
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
    } else { // mDirection == EHint::VERTICAL // default
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
