#ifndef __cym_uix_clayout_hpp__
#define __cym_uix_clayout_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
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
          virtual bool  area(const SArea&) = 0;
          virtual bool  calc() = 0;
      };
      template <typename T> class TItem : public BItem {
        protected:
          T mItem;
        public:
          TItem(T, int = 0);
          virtual CObject* operator ->() override;
        public:
          virtual bool area(const SArea&) override;
          virtual bool calc() override;
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
      EHint               mDirection = {EHint::VERTICAL};
      std::vector<BItem*> mItems;
    public:
      CBoxLayout(                    EHint);
      CBoxLayout(CWindow* = nullptr, EHint = EHint::VERTICAL);
      ~CBoxLayout();
    public:
      BItem* operator [](typename decltype(mItems)::size_type i);
    protected:
      virtual bool calc() override;
    public:
      BItem*   item(typename decltype(mItems)::size_type i);
      CWindow* add(CWindow*, int = 0);
      CLayout* add(CLayout*, int = 0);
  };
}}

#endif //__cym_uix_clayout_hpp__
