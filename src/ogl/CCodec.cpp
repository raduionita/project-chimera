#include "ogl/CCodec.hpp"
#include "sys/CException.hpp"

namespace ogl {
  CCodec::CCodec(const char* type) {
    CCodecManager::codec(type, this);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CDDSCodec* CDDSCodec::sInstance {new CDDSCodec};
  
  PResourceData CDDSCodec::decode(const sys::CFile& file) const {
    log::nfo << "ogl::CDDSCodec::decode(sys::CFile&)::" << this << " FILE:" << file << log::end;
    
    sys::throw_if(!able(file), "Cannot decode this ["+ file +"] file", __FILE__, __LINE__);
    
    sys::throw_if(!file.open(), "Cannot open "+ file, __FILE__, __LINE__);
    
    char ftyp[3];
    file.read(ftyp, 4);
    
    sys::throw_if(::strncmp(ftyp, "DDS", 4) != 0, "Not a .DDS file", __FILE__, __LINE__);
    
    SHeader head;
    file.read((char*)(&head), sizeof(head));
    
    if ((head.caps2 & EFlag::CUBEMAP)) {
      pTexture->type(CTexture::EType::CUBEMAP);
    } else if ((head.caps2 & EFlag::VOLUME) && (head.depth > 0)) {
      pTexture->type(CTexture::EType::VOLUME);
    }
    
    CTextureData* data = new CTextureData;
    
    return PResourceData(data);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  sys::CMap<sys::CString, CCodec*> CCodecManager::sCodecs {};
}
