#include "uix/CDialog.hpp"

namespace uix {
  CFileDialog::CFileDialog(const std::vector<std::string>& aTypes/*={*.*}*/, const CString& tTitle/*=""*/, uint nHints/*=0*/) : mTypes{aTypes}, mHints{nHints} {
    SYS_LOG_NFO("uix::CFileDialog::CFileDialog(std::vector&,CString&,int)::" << this);
    CFileDialog::init(nullptr,tTitle,AUTO,nHints);
  }
  
  CFileDialog::CFileDialog(CWindow* pParent, const std::vector<std::string>& aTypes/*={*.*}*/, const CString& tTitle/*=""*/, uint nHints/*=0*/) : mTypes{aTypes}, mHints{nHints} {
    SYS_LOG_NFO("uix::CFileDialog::CFileDialog(CWindow*,std::vector&,CString&,int)::" << this);
    CFileDialog::init(pParent,tTitle,AUTO,nHints);
  }

  CFileDialog::~CFileDialog() {
    SYS_LOG_NFO("uix::CFileDialog::~CFileDialog()::" << this);
    CFileDialog::free();
  }
  
  bool CFileDialog::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=EDialog::DIALOG|EDialog::MUSTEXIST*/) {
    SYS_LOG_NFO("uix::CFileDialog::init(CWindow*,CString&,SArea&,uint)::" << this);
    
    RETURN((mState & EState::INITED),true);
    
    (mParent) && (mParent->assign(this));
    
    ::ZeroMemory(&mOFN, sizeof(mOFN)); // Initialize OPENFILENAME
    
    mOFN.lStructSize     = sizeof(mOFN);
    mOFN.hwndOwner       = mParent ? (HWND)(*mParent) : NULL;
  //mOFN.lpstrFile       = szFile;
  //mOFN.lpstrFile[0]    = '\0';
  //mOFN.nMaxFile        = sizeof(szFile);
    mOFN.nFilterIndex    = 1;
    mOFN.lpstrFileTitle  = NULL;
    mOFN.lpstrTitle      = tTitle.size() > 0 ? tTitle.c_str() : NULL;
    mOFN.nMaxFileTitle   = 0;
    mOFN.lpstrInitialDir = NULL;
    mOFN.Flags           = mHints & EDialog::MUSTEXIST ? OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST : 0; // OFN_FORCESHOWHIDDEN
    mOFN.lpfnHook        = CFileDialog::proc;
    mOFN.lCustData       = (LPARAM)this;
    mOFN.lpstrFilter     = "All\0*.*\0Text\0*.TXT\0";
  //oOFN.nFileExtension = 
  
    if (mTypes.size()) {
      std::string tFilter;
      for (int i = 0; i < mTypes.size(); i++) {
        tFilter.append(mTypes[i] + '\0' + mTypes[i] + '\0');
      }
      mOFN.lpstrFilter = tFilter.c_str();
    }
    
    // OFN_FORCESHOWHIDDEN
    // OFN_HIDEREADONLY
    // OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST
    // OFN_EXPLORER | OFN_ALLOWMULTISELECT
    // OFN_EXPLORER|OFN_ENABLEHOOK|OFN_ENABLESIZING
    // OFN_NOCHANGEDIR
    // OFN_OVERWRITEPROMPT
    // OFN_ENABLETEMPLATEHANDLE
    
    return (mState = mState | EState::INITED);
  }
  
  bool CFileDialog::free() {
    SYS_LOG_NFO("uix::CFileDialog::free()::" << this);
    
    return true;
  }
  
  bool CFileDialog::show(uint nHints/*=EDialog::OPEN*/) {
    char szFile[256];
    mOFN.lpstrFile       = szFile;
    mOFN.lpstrFile[0]    = '\0';
    mOFN.nMaxFile        = sizeof(szFile);
    
    if ((nHints & EDialog::OPEN) && (::GetOpenFileName(&mOFN) == TRUE)) {
      mFile = mOFN.lpstrFile;
      return true;
    } else if ((nHints & EDialog::SAVE) && (::GetSaveFileName(&mOFN) == TRUE)) {
      mFile = mOFN.lpstrFile;
      return true;
    } else {
      SYS_LOG_NFO("[CFileDialog] ::Get[Open/Save]FileName() CANCELED!");
      return false;
    }
  }
  
  UINT_PTR CALLBACK CFileDialog::proc(HWND hDlg, UINT uMsg, WPARAM UNUSED(wParam), LPARAM lParam) {
    log::dbg << "uix::CFileDialog::proc(HWND,UINT,WPARAM,LPARAM)" << log::end;
    switch (uMsg) {
      case WM_INITDIALOG: {
        OPENFILENAME* oOFN   = reinterpret_cast<OPENFILENAME *>(lParam);
        CFileDialog* pDialog = reinterpret_cast<CFileDialog*>(oOFN->lCustData);
        
        SYS_LOG_NFO("  D::WM_INITDIALOG::" << pDialog << " ID:" << pDialog->mId);
        
        // on init dialog
        
      } break;
      case WM_NOTIFY: {
        const NMHDR* pNM = reinterpret_cast<NMHDR*>(lParam);
        if (pNM->code > CDN_LAST && pNM->code <= CDN_FIRST) {
          const OFNOTIFY* pNotify = reinterpret_cast<OFNOTIFY*>(lParam);
          CFileDialog* pDialog = reinterpret_cast<CFileDialog*>(pNotify->lpOFN->lCustData);
          
          SYS_LOG_NFO("  D::WM_NOTIFY::" << pDialog << " ID:" << pDialog->mId << " CODE:" << pNotify->hdr.code);
          
          switch (pNotify->hdr.code) {
            case CDN_INITDONE: {
              // pDialog-> on init done
            } break;
            case CDN_SELCHANGE: {
              // pDialog -> on sel change
            } break;;
            case CDN_TYPECHANGE: {
              // pDialog -> on type change (  (WXHWND)hDlg, pNotifyCode->lpOFN->nFilterIndex)
            } break;
          }
        }
      } break;
      case WM_DESTROY: {
        OPENFILENAME* oOFN   = reinterpret_cast<OPENFILENAME *>(lParam);
        CFileDialog* pDialog = reinterpret_cast<CFileDialog*>(oOFN->lCustData);
        
        SYS_LOG_NFO("  D::WM_DESTROY::" << pDialog << " ID:" << pDialog->mId);
      } break;
    }
    
    return 0;
  }
}
