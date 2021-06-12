#ifndef __uix_cdialog_hpp__
#define __uix_cdialog_hpp__

#include "uix/uix.hpp"
#include "uix/CPopup.hpp"
#include "sys/CFile.hpp"

namespace uix {
  class CDialog : public CPopup {
      friend class CFileDialog;
    protected:
      using CPopup::CPopup;
      using CPopup::operator=;
      typedef CPopup super;
      static constexpr int WINDOW = CPopup::WINDOW;
  };
  
  class CFileDialog: public CDialog {
    protected:
      using CDialog::CDialog;
      using CDialog::operator=;
      typedef CDialog      super;
      static constexpr int WINDOW = CDialog::WINDOW;
    protected:
      sys::CFile               mFile;
      std::vector<std::string> mTypes {"*.*"};
      uint                     mHints {ZERO};
      OPENFILENAME             mOFN;
    public:
      CFileDialog(          const std::vector<std::string>& aTypes = {"*.*"}, const CString& = "", uint = EDialog::DIALOG | EDialog::MUSTEXIST);
      CFileDialog(CWindow*, const std::vector<std::string>& aTypes = {"*.*"}, const CString& = "", uint = EDialog::DIALOG | EDialog::MUSTEXIST);
      ~CFileDialog();
    protected:
      virtual bool init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = EDialog::DIALOG | EDialog::MUSTEXIST) override;
      virtual bool free() override;
    public:
      inline sys::CFile& getFile() { return mFile; }
    public:
      virtual bool show(uint = EDialog::OPEN) override;
    protected:
      static UINT_PTR CALLBACK proc(HWND, UINT, WPARAM, LPARAM);
  };
}

#endif //__uix_cdialog_hpp__
