#include <type_traits>
#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CException.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"

namespace ogl {
  CTexture::CTexture() /*default*/ {
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::CTexture(PTextureStream stream) {
    load(stream);
  }
  
  CTexture::CTexture(GLenum target) : mTarget{target} {
    GLCALL(::glGenTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  CTexture::CTexture(EType t) : mType{t} {
    type(mType);
    GLCALL(::glGenTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  CTexture::~CTexture() {
    GLCALL(::glDeleteTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, 0));
  }
  
  void CTexture::load(PTextureStream) {
    log::nfo << "ogl::CTexture::load(PTextureStream)::" << this << log::end;
// @todo: create the texture
  }
  
  GLvoid CTexture::bind(bool state/*=true*/) const {
    if (state) {
      GLCALL(::glActiveTexture(GL_TEXTURE0 + mSlot));
      GLCALL(::glBindTexture(mTarget, mID));
    } else {
      GLCALL(::glActiveTexture(GL_TEXTURE0));
      GLCALL(::glBindTexture(mTarget, 0));
    }
  }
  
  GLvoid CTexture::bind(GLuint slot) {
    GLCALL(::glActiveTexture(GL_TEXTURE0 + (mSlot = slot)));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  GLvoid CTexture::sampler(ogl::CShader*) {
    throw CException("NOT IMPLEMENTED");
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { 
    reader(new CDdsTextureReader);
  }
  
  CTextureManager::~CTextureManager() { }
  
  PTexture CTextureManager::load(const sys::CFile& file, const sys::CString& name/*=""*/) {
    log::nfo << "ogl::CTextureManager::load(CFile&,CString&)::" << this << " FILE:" << file << " NAME:" << name << log::end;
    PTexture pTexture;
// @todo: if name is empty then name = filename.ext
// @todo: search cache

    PTextureReader pReader = sys::static_pointer_cast<PTextureReader::type>(reader(file.ext()));
    if (pReader) {
      pTexture = CTexture::from(pReader->read(file));
      
      
      
    } else {
// @todo: pTexture = NULL Texture
// @todo: cache null texture
    }
    



    // use file loader


// @todo: update cache
    return pTexture;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PTextureStream CDdsTextureReader::read(const sys::CFile& file) {
    log::nfo << "ogl::CDdsTextureReader::read(CFile&)::" << this << " FILE:" << file << log::end;
    PTextureStream stream {new CTextureStream};
    
    sys::throw_if(!file.open(), "Cannot open file!"); // + file.path());
    
    char ftype[4];
    file.read(ftype, 4);
    sys::throw_if(::strncmp(ftype, "DDS ", 4) != 0, "File not of .DDS format!");
    
    SHeader head;
    file.read((byte*)(&head), sizeof(head));
    
    if(head.caps2 & DDS_CUBEMAP) {
      stream->set(CTexture::EFlag::CUBEMAP);
    } else if((head.caps2 & DDS_VOLUME) && (head.depth > 0)) {
      stream->mMeta.flags |= CTexture::EFlag::VOLUME;
    } else {
      stream->set(CTexture::EFlag::PLANEMAP);
    }
    
    uint faces    = stream->add(CTexture::EFlag::CUBEMAP) ? 6 : 1;
    uint channels = head.format.fourcc == DDS_FOURCC || head.format.bpp == 24 ? 3 : 4;
    
    if (head.format.flags & DDS_FOURCC) {
      switch (head.format.fourcc) {
        case DDS_FOURCC_DTX1:
          stream->set(CTexture::EFlag::RGBA_S3TC_DXT1);
        case DDS_FOURCC_DTX3:
          stream->set(CTexture::EFlag::RGBA_S3TC_DXT3);
        case DDS_FOURCC_DTX5:
          stream->add(CTexture::EFlag::RGBA_S3TC_DXT5);
      }
      stream->add(CTexture::EFlag::COMPRESSED);
    } else if(head.format.flags == DDS_RGBA && head.format.bpp == 32) {
      stream->add(CTexture::EFlag::RGBA);
    } else if(head.format.flags == DDS_RGB && head.format.bpp == 32) {
      stream->add(CTexture::EFlag::RGBA);
    } else if(head.format.flags == DDS_RGB && head.format.bpp == 24) {
      stream->add(CTexture::EFlag::RGB);
    } else if(head.format.bpp == 8) {
      stream->add(CTexture::EFlag::LUMINANCE);
    } else {
      sys::throw_if(true, "Pixel format not supported!");
    }
    
    stream->width(head.width);
    stream->height(clamp2one(head.height));
    stream->depth(clamp2one(head.depth));
    stream->mipmaps(clamp2one(head.mipmapcount));
    
    uint size = 0;
    
    ubyte* data = stream->data(size);
    
    // bind
    // glPixelStorei
    
    uint  width   = 0;
    uint  height  = 0;
    uint  depth   = 0;
    uint& mipmaps = stream->mipmaps;
    uint& flags   = stream->flags;
    for(uint i = 0; i < faces; i++) {
      
      width  = head.width;
      height = head.height;
      depth  = head.depth ? head.depth : 1;
      
      for(ushort j = 0; j < mipmaps && (width || height); j++) {
        
        uint   bufsize = mapsize(width, height, depth, channels, flags);
        ubyte* buffer  = new ubyte[bufsize];
        
        
        
        
        width  = clamp2one(width  >> 1);
        height = clamp2one(height >> 1);
        depth  = clamp2one(depth  >> 1);
      }
    }
    
    return stream;
  }
}
