#include "cym/uix/CLayout.hpp"
#include "cym/uix/CWindow.hpp"

namespace cym { namespace uix {
  CLayout::CLayout(CWindow* pWindow/*=nullptr*/) {
    std::cout << "uix::CLayout::CLayout(CWindow*)::" << this << std::endl;
  }
  
  CLayout::~CLayout() {
    std::cout << "uix::CLayout::~CLayout()::" << this << std::endl;
  }
  
  bool CLayout::layout(CWindow* pWindow, int nHints/*=0*/) {
    std::cout << "uix::CLayout::layout(CWindow*)::" << this << std::endl;
    mWindow = pWindow;
    return calc();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  CLayout::BItem::BItem(int hints/*=0*/) : mHints(hints) {}
   
  CLayout::BItem::~BItem() {}
  
  template <typename T> CLayout::TItem<T>::TItem(T item, int hints/*=0*/) : BItem(hints), mItem(item) {}
  
  template <typename T> CObject* CLayout::TItem<T>::operator ->() { return mItem; }
    
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
    
    // @todo: get mWindow client w & h
    
    if (mDirection == EHint::HORIZONTAL) {
      // for each item
      for (int i = 0; i < nItems; i++) {
        BItem*& pItem = mItems[i];
        // @todo: pItem->size() // which delegates to CWindow/CLayout 
        // @todo: pItem->move() // 
      }
    } else { // mDirection == EHint::VERTICAL // default
      for (int i = 0; i < nItems; i++) {
        BItem*& pItem = mItems[i];
        
      }
    }
    
    // @todo: read hints
    // @todo: vertical: stack (onty) 1 on top of another | 1 per row
      // @todo: for each item in items 
      // @todo: device equally 
      // @todo: resize window/layout (if layout, that will trigger another layout internal resize)
    
    // @todo: horizontal: 1 per column | divided equally 
    
    // @todo: hint:ADJUST => on resize to item's w & h
    
    return true;
  }
}}
