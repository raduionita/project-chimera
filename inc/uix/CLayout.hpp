#ifndef __uix_clayout_hpp__
#define __uix_clayout_hpp__

#include "uix/uix.hpp"
#include "uix/CObject.hpp"
#include "uix/CWindow.hpp"

namespace uix {
  class CLayout : public CObject {
      friend class CWindow;
    protected:
      using CObject::CObject;
      using CObject::operator=;
    protected:
      class CItem {
        protected:
          int   mHints = {0};
          SArea mArea  = AUTO;
        public:
          CItem(int = 0, const SArea& = AUTO);
          virtual ~CItem();
          virtual CObject* operator ->() = 0;
        public:
          virtual bool   area(const SArea&) = 0;
          inline  SArea& area() { return mArea; }
          inline  int&   hints() { return mHints; } 
      };
      template<typename T> class TItem : public CItem {
        protected:
          T* mObject;
        public:
          TItem(T* pItem, int nHints = 0, const SArea& tArea = AUTO) : CItem{nHints,tArea}, mObject{pItem} {}
          virtual CObject* operator ->() override { return mObject; };
        public:
          virtual bool area(const SArea& tArea) override { 
            // CWindow or CLayout 's area
            auto  sArea = mObject->area(); // {0,0,320,480} {320,0,320,480}
            // win.area.xy = itm.area.xy + ...
            sArea.x = tArea.x + ((mHints & ELayout::ADJUST) || (mHints & ELayout::LEFT) ? 0 // 0 = don't add anyting // if ADJUST or LEFT 
                                                                                        : ((mHints & ELayout::RIGHT)  ? (tArea.w - sArea.w) // itm.w - win.w = where x should be // if RIGHT
                                                                                                                      : ((mHints & ELayout::CENTER) ? ((tArea.w - sArea.w)/2) // mid x = half itm.w - half wnd.x //
                                                                                                                                                    : (mArea.x)))); // wnd.x pos inside itm
            sArea.y = tArea.y + ((mHints & ELayout::ADJUST) || (mHints & ELayout::TOP)  ? 0
                                                                                        : ((mHints & ELayout::BOTTOM) ? (tArea.h - sArea.h)
                                                                                                                      : ((mHints & ELayout::CENTER) ? ((tArea.h - sArea.h)/2)
                                                                                                                                                    : (mArea.y)))); // mArea set on item add
            // win.area.wh = itm.area.wh OR same
            sArea.w = (mHints & ELayout::ADJUST) || (sArea.w == AUTO) 
              ? tArea.w 
              : sArea.w;
            sArea.h = (mHints & ELayout::ADJUST) || (sArea.h == AUTO) 
              ? tArea.h 
              : sArea.h;
            // debug
            CYM_LOG_NFO("uix::CLayout::TItem::area(SArea&)" << " " << sArea);
            // return calculated area 
            return mObject->area(sArea); // CWindow or CLayout
          }
      };
    protected:
      CWindow* mWindow = {nullptr};
      SArea    mArea   = {0};
      int      mHints  = {int(ELayout::ADJUST)};
    public:
      inline CLayout(int eHints = int(ELayout::LAYOUT)) :        mArea{AUTO},  mHints{eHints|ELayout::ADJUST} { CYM_LOG_NFO("uix::CLayout::CLayout(int)::" << this); }
      inline CLayout(int eHints,    const SArea& tArea = AUTO) : mArea{tArea}, mHints{eHints}                 { CYM_LOG_NFO("uix::CLayout::CLayout(SArea&,int)::" << this); }
      inline CLayout(ELayout eHint, const SArea& tArea = AUTO) : mArea{tArea}, mHints{eHint|ELayout::LAYOUT}  { CYM_LOG_NFO("uix::CLayout::CLayout(SArea&,ELayout)::" << this); }
      inline ~CLayout() { CYM_LOG_NFO("uix::CLayout::~CLayout()::" << this); }
    protected:
      virtual bool area(const SArea&);
    public:
      inline  SArea  area()  { return mArea; }
      inline  int    hints() const { return mHints; }
      virtual bool   apply(CWindow* pWindow = nullptr);
  };

  class CBoxLayout : public CLayout {
      friend class CItem;
    public:
      using ELayout = uix::ELayout;
    protected:
      std::vector<CItem*> mItems;
    public:
      CBoxLayout() = default;
      inline ~CBoxLayout() { CYM_LOG_NFO("uix::CBoxLayout::~CBoxLayout()::" << this); for (auto pItem : mItems) delete pItem; }
      using CLayout::CLayout;
      using CLayout::operator=;
    public:
      inline CItem* operator [](typename decltype(mItems)::size_type i) { return mItems[i]; }
    protected:
      virtual bool area(const SArea&) override;
    public:
      using CLayout::area;
      CItem*   item(typename decltype(mItems)::size_type i);
      CWindow* add(CWindow* pWindow, const ELayout& eLayout = ELayout::LAYOUT);
      CLayout* add(CLayout* pLayout, const ELayout& eLayout = ELayout::LAYOUT);
  };
}

#endif //__uix_clayout_hpp__
