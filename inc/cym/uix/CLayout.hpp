#ifndef __cym_uix_clayout_hpp__
#define __cym_uix_clayout_hpp__

#include "CObject.hpp"

namespace cym::uix {
  class CLayout : public CObject {
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      class BItem {
        protected:
          int   mHints = {0};
          SArea mArea  = {0};
        public:
          BItem(int = 0);
          virtual ~BItem();
          virtual CObject* operator ->() = 0;
        public:
          virtual bool area(const SArea&) = 0;
          virtual bool calc() = 0;
      };
      template <typename T> class TItem : public BItem {
        protected:
          T mItem;
        public:
          TItem(T pItem, int nHints = 0) : BItem(nHints), mItem(pItem) {}
          virtual CObject* operator ->() override { return mItem; };
        public:
          virtual bool area(const SArea& sArea) override { mArea = sArea; return calc(); }
          virtual bool calc() override  {
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
            // return calculated area 
            return mItem->area({std::max(0, sArea.x), std::max(0, sArea.y), sArea.w, sArea.h});
          }
      };
    protected:
      CWindow* mWindow = {nullptr};
      SArea    mArea   = {0};
    public:
      CLayout(CWindow* = nullptr);
      ~CLayout();
    protected:
      virtual SArea area() const;
      virtual bool  area(const SArea&);
      virtual bool  calc() = 0;
    public:
      virtual bool layout(CWindow*);
  };
  
  class CBoxLayout : public CLayout {
    protected:
      using CLayout::CLayout;
      using CLayout::operator=;
    protected:
      ELayout             mDirection = {ELayout::VERTICAL};
      std::vector<BItem*> mItems;
    public:
      CBoxLayout(                    ELayout);
      CBoxLayout(CWindow* = nullptr, ELayout = ELayout::VERTICAL);
      ~CBoxLayout();
    public:
      BItem* operator [](typename decltype(mItems)::size_type);
    protected:
      virtual bool calc() override;
    public:
      BItem*   item(typename decltype(mItems)::size_type i);
      template <typename T> decltype(auto) add(T* item, const ELayout& eLayout = ELayout::EMPTY) {
        log::nfo << "uix::CBoxLayout::add(T*,int)::" << this << log::end;
        mItems.push_back(std::move(new TItem<T*>(item,int(eLayout))));
        return item;
      }
  };
}

#endif //__cym_uix_clayout_hpp__
