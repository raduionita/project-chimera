#ifndef __cym_uix_clayout_hpp__
#define __cym_uix_clayout_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CLayout : public CObject {
    protected:
      class BItem {
        protected:
          int mHints = {0};
        public:
          BItem(int = 0);
          virtual ~BItem();
          virtual CObject* operator ->() = 0;
      };
      template <typename T> class TItem : public BItem {
        protected:
          T mItem;
        public:
          TItem(T, int = 0);
          virtual CObject* operator ->() override;
      };
    protected:
      CWindow* mWindow = {nullptr};
    public:
      CLayout(CWindow* = nullptr);
      ~CLayout();
    protected:
      virtual bool calc() = 0;
    public:
      virtual bool layout(CWindow*, int = 0);
  };
  
  class CBoxLayout : public CLayout {
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
      BItem* item(typename decltype(mItems)::size_type i);
      CWindow* add(CWindow*, int = 0);
      CLayout* add(CLayout*, int = 0);
  };
}}

#endif //__cym_uix_clayout_hpp__
