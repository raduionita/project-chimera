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
  
  CTexture::~CTexture() {
    GLCALL(::glDeleteTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, 0));
  }
  
  void CTexture::load(PTextureStream stream) {
    log::nfo << "ogl::CTexture::load(PTextureStream)::" << this << log::end;
    CTextureStream::SInfo& info = stream->mInfo;
    
    static GLenum targets[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    uint   faces    = info.flags & EFlag::CUBEMAP ? 6 : 1;
    uint   channels = info.bpp == 24 ? 3 : 4;
    uint   width    = 0;
    uint   height   = 0;
    uint   depth    = 0;
    uint   size     = 0;
    uint&  mipmaps  = info.mipmaps;
    uint   flags    = info.flags | EFlag::MIPMAPED;
    byte*  data     = stream->ptr();
    GLenum target   = (flags & EFlag::CUBEMAP) ? GL_TEXTURE_CUBE_MAP : (flags & EFlag::VOLUME) ? GL_TEXTURE_3D : GL_TEXTURE_2D;
    GLenum internal = flags & EFlag::RGBA_S3TC_DXT1 ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : flags & EFlag::RGBA_S3TC_DXT3 ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT : flags & EFlag::RGBA_S3TC_DXT5 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : flags & EFlag::RGBA ? GL_RGBA : flags & EFlag::RGB ? GL_RGB : GL_LUMINANCE;
    GLenum format   = GL_RGBA; // GL_RED, GL_RG, GL_RGB,...
    GLenum type     = GL_UNSIGNED_BYTE;
    
    mTarget = target;
    mFormat = internal;
    
    GLCALL(::glGenTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, mID));
    GLCALL(::glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_BASE_LEVEL, 0));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAX_LEVEL, mipmaps));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    
// @todo: this might not be good for all formats

    for (uint i = 0; i < faces; i++) {
      if(faces > 1) target = targets[i];
      width  = info.width;
      height = info.height;
      depth  = info.depth;
      for (ushort j = 0; j < mipmaps && (width || height); j++) {
        size  += CTextureStream::mapsize(width, height, depth, channels, flags);
        if (flags & EFlag::COMPRESSED) {
          if (flags & EFlag::VOLUME)
            GLCALL(::glCompressedTexImage3D(target, j, internal, width, height, depth, 0, size, data));
          else
            GLCALL(::glCompressedTexImage2D(target, j, internal, width, height, 0, size, data));
        } else {
          if (flags & EFlag::VOLUME) {
            GLCALL(::glTexImage3D(target, j, internal, width, height, depth, 0, format, type, data));
          }
          else
            GLCALL(::glTexImage2D(target, j, internal, width, height, 0, format, type, data));
        }
        data += size;
      }
    }
    
    if (mipmaps <= 1 && flags & EFlag::MIPMAPED) {
      GLCALL(::glGenerateMipmap(mTarget));
    }
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
  
  GLvoid CTexture::bind(GLint slot) {
    GLCALL(::glActiveTexture(GL_TEXTURE0 + (mSlot = slot)));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  GLvoid CTexture::sampler(ogl::CShader*) {
    throw CException("NOT IMPLEMENTED");
  }
  
  void CTexture::filtering(enum ogl::CTexture::EFiltering eFiltering) {
    GLCALL(::glBindTexture(mTarget, mID));
    switch(eFiltering) {
      case EFiltering::NEAREST:
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
          // sys::info << " > INFO: NEAREST" << sys::endl;
      break;
      default:
      case EFiltering::BILINEAR:
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        // sys::info << " > INFO: BILINEAR" << sys::endl;
      break;
      case EFiltering::TRILINEAR:
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        // sys::info << " > INFO: TRILINEAR" << sys::endl;
      break;
      case EFiltering::ANISOTROPIC:
        // sys::info << " > INFO: ANISOTROPIC" << sys::endl;
      break;
    }
  }
  
  void CTexture::wrapping(enum ogl::CTexture::EWrapping eWrapping) {
    GLCALL(::glBindTexture(mTarget, mID));
      
    GLenum wrapping = GL_NONE;
    if(eWrapping | EWrapping::CLAMP_TO_EDGE)
      wrapping = GL_CLAMP_TO_EDGE;
    else if(eWrapping | EWrapping::CLAMP_TO_BORDER)
      wrapping = GL_CLAMP_TO_BORDER;
    else if(eWrapping | EWrapping::REPEAT)
      wrapping = GL_REPEAT;
      
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, wrapping));
    if(mHeight > 1 || mTarget == GL_TEXTURE_2D || mTarget == GL_TEXTURE_1D_ARRAY)
      GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, wrapping));
    if(mDepth > 1 || mTarget == GL_TEXTURE_3D || mTarget == GL_TEXTURE_CUBE_MAP || mTarget == GL_TEXTURE_2D_ARRAY)
      GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, wrapping));
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() {
    loader(new CFileTextureLoader);
  }
  
  CTextureManager::~CTextureManager() { }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PTextureStream CFileTextureLoader::load(const sys::CFile &file) {
    log::nfo << "ogl::CFileTextureLoader::load(CFile&)::" << this << " FILE:" << file << log::end;  
    // start w/ a stream
    CTextureStream* pStream {new CTextureStream};  
    
    
    
    return pStream;
  }
  
  
  // PTextureStream CDdsTextureLoader::load(const sys::CFile& file) {
  //   log::nfo << "ogl::CDdsTextureLoader::load(CFile&)::" << this << " FILE:" << file << log::end;
  //   CTextureStream*       stream {new CTextureStream};
  //   CTextureStream::SInfo info {}; 
  //  
  //   sys::throw_if(!file.open(), "Cannot open file!"); // + file.path());
  //  
  //   char ftype[4];
  //   file.read(ftype, 4);
  //   sys::throw_if(::strncmp(ftype, "DDS ", 4) != 0, "File not of .DDS format!");
  //  
  //   SHeader head;
  //   file.read((byte*)(&head), sizeof(head));
  //  
  //   if(head.caps2 & DDS_CUBEMAP) {
  //     info.flags |= CTexture::EFlag::CUBEMAP;
  //   } else if((head.caps2 & DDS_VOLUME) && (head.depth > 0)) {
  //     info.flags |= CTexture::EFlag::VOLUME;
  //   } else {
  //     info.flags |= CTexture::EFlag::PLANEMAP;
  //   }
  //  
  //   uint faces    = info.flags & CTexture::EFlag::CUBEMAP ? 6 : 1;
  //   uint channels = head.format.fourcc == DDS_FOURCC || head.format.bpp == 24 ? 3 : 4;
  //  
  //   if (head.format.flags & DDS_FOURCC) {
  //     switch (head.format.fourcc) {
  //       case DDS_FOURCC_DTX1: info.flags |= CTexture::EFlag::RGBA_S3TC_DXT1; break;
  //       case DDS_FOURCC_DTX3: info.flags |= CTexture::EFlag::RGBA_S3TC_DXT3; break;
  //       case DDS_FOURCC_DTX5: info.flags |= CTexture::EFlag::RGBA_S3TC_DXT5; break;
  //     }
  //     info.flags |= CTexture::EFlag::COMPRESSED;
  //   } else if(head.format.flags == DDS_RGBA && head.format.bpp == 32) {
  //     info.flags |= CTexture::EFlag::RGBA;
  //   } else if(head.format.flags == DDS_RGB && head.format.bpp == 32) {
  //     info.flags |= CTexture::EFlag::RGBA;
  //   } else if(head.format.flags == DDS_RGB && head.format.bpp == 24) {
  //     info.flags |= CTexture::EFlag::RGB;
  //   } else if(head.format.bpp == 8) {
  //     info.flags |= CTexture::EFlag::LUMINANCE;
  //   } else {
  //     sys::throw_if(true, "Pixel format not supported!");
  //   }
  //  
  //   info.bpp     = head.format.bpp;
  //   info.width   = head.width;
  //   info.height  = CTextureStream::clamp2one(head.height);
  //   info.depth   = CTextureStream::clamp2one(head.depth);
  //   info.mipmaps = CTextureStream::clamp2one(head.mipmapcount);
  //  
  //   uint  width   = 0;
  //   uint  height  = 0;
  //   uint  depth   = 0;
  //   uint& mipmaps = info.mipmaps;
  //   uint& flags   = info.flags;
  //   for(uint i = 0; i < faces; i++) {
  //     width  = head.width;
  //     height = head.height;
  //     depth  = head.depth ? head.depth : 1;
  //     for (ushort j = 0; j < mipmaps && (width || height); j++) {
  //       info.size  += CTextureStream::mapsize(width, height, depth, channels, flags);
  //       width       = CTextureStream::clamp2one(width  >> 1);
  //       height      = CTextureStream::clamp2one(height >> 1);
  //       depth       = CTextureStream::clamp2one(depth  >> 1);
  //      
  //     }
  //   }
  //  
  //   byte* data = stream->data(info.size);
  //   uint  size = 0;
  //   for(uint i = 0; i < faces; i++) {
  //     width  = head.width;
  //     height = head.height;
  //     depth  = head.depth ? head.depth : 1;
  //     for(ushort j = 0; j < mipmaps && (width || height); j++) {
  //       size = CTextureStream::mapsize(width, height, depth, channels, flags);
  //       file.read(data,size);
  //       data += size;
  //       width  = CTextureStream::clamp2one(width  >> 1);
  //       height = CTextureStream::clamp2one(height >> 1);
  //       depth  = CTextureStream::clamp2one(depth  >> 1);
  //     }
  //   }
  //  
  //   stream->info(info);
  //   return stream;
  // }
}
