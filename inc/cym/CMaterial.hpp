#ifndef __cym_cmaterial_hpp__
#define __cym_cmaterial_hpp__

#include "sys/CException.hpp"
#include "cym/CResource.hpp"
#include "cym/CTexture.hpp"

namespace cym {
  class CMaterialData; typedef sys::TPointer<CMaterialData> PMaterialData;
  class CChannel; typedef sys::TPointer<CChannel> PChannel;
  
  class CChannel {
    public:
      enum EType : int {
        NONE     = 0,
        DIFFUSE  =  1,
        AMBIENT  =  2,
        NORMAL   =  4,
        SPECULAR =  8,
        EMISSION = 16,
        OPACITY  = 32,
      };
    public:
      virtual inline EType getType() const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__);  }; 
  };
  
  class CMaterial : public CResource {
    protected:
      sys::CTable<sys::CString,PChannel> mChannels;
      float                              mIOR;
      float                              mShininess;
      bool                               mTransparent {false}; // update on material creation
    public:
      using cym::CResource::CResource;
    public:
      CMaterial();
      ~CMaterial();
    public:
      inline bool isTransparent() const { return mTransparent; }  
  };
    
  class NChannel : public TNode<cym::CChannel> {
    protected:
    //cym::PChannel mResource;
  };
  
  class NMaterial : public TNode<cym::CMaterial> {
    protected:
      sys::CCollection<NChannel> mChannels;
  };
  
  
  // indo ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CChannelInfo {
    public:
      // identifier
      sys::string  name;
      // fields
      sys::string  type;
      cym::STextureInfo texture;
  };
    
  class CMaterialInfo {
    public:
      // identifier
      sys::string               name;
      // fields
      sys::vector<CChannelInfo> channels;
  };
  
  // specific ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CDiffuseChannel : public CChannel {
    protected:
      cym::CColor   mColor;
      cym::PTexture mTexture;
    public:
      virtual inline EType getType() const override { return EType::DIFFUSE; }
  };
  
  class CNormalChannel : public CChannel {
    protected:
      cym::PTexture mTexture;
    public:
      virtual inline EType getType() const override { return EType::AMBIENT; }
  };
  
  class CSpecularChannel : public CChannel {
    protected:
      cym::CColor   mColor;
      cym::PTexture mTexture;
    public:
      virtual inline EType getType() const override { return EType::SPECULAR; }
  };
  
  class CEmissionChannel : public CChannel {
    protected:
      cym::CColor   mColor;
      cym::PTexture mTexture;
    public:
      virtual inline EType getType() const override { return EType::EMISSION; }
  };
  
  class COpacityChannel : public CChannel {
    protected:
      float         mValue;
      cym::PTexture mTexture;
    public:
      virtual inline EType getType() const override { return EType::OPACITY; }
  };
  
  // class CStandartMaterial
  // class CMultipleMaterial
}

#endif //__cym_cmaterial_hpp__
