#include "cym/CCodec.hpp"
#include "sys/CParser.hpp"

namespace cym {
  // manager //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CCodecManager::addCodec(const sys::sptr<CCodec> pCodec) {
    CYM_LOG_NFO("cym::CCodecManager::addCodec(sys::sptr<CCodec>)::" << pCodec->getType());
    static auto pThis {cym::CCodecManager::getSingleton()};
    pThis->mCodecs.insert(std::pair(pCodec->getType(), pCodec));
  }
  
  sys::sptr<CCodec> CCodecManager::getCodec(const std::string& ext) {
    CYM_LOG_NFO("cym::CCodecManager::getCodec(std::string&)::" << ext);
    static auto self {cym::CCodecManager::getSingleton()};
    auto it = self->mCodecs.find(ext);
    if (it == self->mCodecs.end())
      throw sys::exception("CANNOT decode "+ ext +" file type!",__FILE__,__LINE__);
    return it->second;
  }
  
  // texture:dds /////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TCodec<CTexture,ECodec::DDS>::decode(sys::sptr<CResourceLoader>& pResourceLoader) {
    auto        pTextureLoader = sys::static_pointer_cast<cym::TTextureLoader<sys::CFile>>(pResourceLoader);
    sys::CFile& rFile          = pTextureLoader->getFile();
    
    CYM_LOG_NFO("cym::TCodec<CTexture,ECodec::DDS>::decode(sys::sptr<CResourceLoader>)::" << this << " FILE:" << rFile);
    
    sys::throw_if(!rFile.open(), "Cannot open DDS file!"); // + rFile.path());
    
    sys::sptr<sys::CStream>& pStream = pTextureLoader->mStream = new sys::CStream;
    
    char ftype[4];
    rFile.read(ftype, 4);
    sys::throw_if(::strncmp(ftype,"DDS ",4) != 0, "File not of .DDS format!");
    
    SHeader oHead;
    rFile.read((byte*)(&oHead), sizeof(oHead));
    
    if(oHead.caps2 & DDS_CUBEMAP) {
      pTextureLoader->flags |= CTexture::EFlag::CUBEMAP;
    } else if((oHead.caps2 & DDS_VOLUME) && (oHead.depth > 0)) {
      pTextureLoader->flags |= CTexture::EFlag::VOLUME;
    } else {
      pTextureLoader->flags |= CTexture::EFlag::PLANEMAP;
    }
    
    uint nFaces    = pTextureLoader->flags & CTexture::EFlag::CUBEMAP ? 6 : 1;
    uint nChannels = oHead.format.fourcc == DDS_FOURCC || oHead.format.bpp == 24 ? 3 : 4;
    
    if (oHead.format.flags & DDS_FOURCC) {
      switch (oHead.format.fourcc) {
        case DDS_FOURCC_DTX1: pTextureLoader->flags |= CTexture::EFlag::RGBA_S3TC_DXT1; break;
        case DDS_FOURCC_DTX3: pTextureLoader->flags |= CTexture::EFlag::RGBA_S3TC_DXT3; break;
        case DDS_FOURCC_DTX5: pTextureLoader->flags |= CTexture::EFlag::RGBA_S3TC_DXT5; break;
      }
      pTextureLoader->flags |= CTexture::EFlag::COMPRESSED;
    } else if(oHead.format.flags == DDS_RGBA && oHead.format.bpp == 32) {
      pTextureLoader->flags |= CTexture::EFlag::RGBA;
    } else if(oHead.format.flags == DDS_RGB && oHead.format.bpp == 32) {
      pTextureLoader->flags |= CTexture::EFlag::RGBA;
    } else if(oHead.format.flags == DDS_RGB && oHead.format.bpp == 24) {
      pTextureLoader->flags |= CTexture::EFlag::RGB;
    } else if(oHead.format.bpp == 8) {
      pTextureLoader->flags |= CTexture::EFlag::LUMINANCE;
    } else {
      throw sys::exception("Pixel format not supported!",__FILE__,__LINE__);
    }
  
    pTextureLoader->bpp     = oHead.format.bpp;
    pTextureLoader->width   = oHead.width;
    pTextureLoader->height  = glm::clamp(oHead.height, 1u);
    pTextureLoader->depth   = glm::clamp(oHead.depth, 1u);
    pTextureLoader->mipmaps = glm::clamp(oHead.mipmapcount, 1u);

    uint  nWidth   {0};
    uint  nHeight  {0};
    uint  nDepth   {0};
    uint& nMipmaps {pTextureLoader->mipmaps};
    uint& nFlags   {pTextureLoader->flags};
    for(uint i = 0; i < nFaces; i++) {
      nWidth  = oHead.width;  
      nHeight = oHead.height;
      nDepth  = oHead.depth ? oHead.depth : 1;
      for (ushort j = 0; j < nMipmaps && (nWidth || nHeight); j++) {
        pTextureLoader->size  += cym::mapsize(nWidth, nHeight, nDepth, nChannels, nFlags);
        nWidth       = glm::clamp(nWidth >> 1);
        nHeight      = glm::clamp(nHeight >> 1);
        nDepth       = glm::clamp(nDepth >> 1);
      }
    }
    
    byte*        pBytes  {pStream->data(pTextureLoader->size)};
    uint         nSize   {0};
    for(uint i = 0; i < nFaces; i++) {
      nWidth  = oHead.width;
      nHeight = oHead.height;
      nDepth  = oHead.depth ? oHead.depth : 1;
      for(ushort j = 0; j < nMipmaps && (nWidth || nHeight); j++) {
        nSize   = cym::mapsize(nWidth, nHeight, nDepth, nChannels, nFlags);
        rFile.read(pBytes, nSize);
        pBytes  += nSize;
        nWidth  = glm::clamp(nWidth >> 1);
        nHeight = glm::clamp(nHeight >> 1);
        nDepth  = glm::clamp(nDepth >> 1);
      }
    }
  }
  
  void TCodec<CTexture,ECodec::TGA>::decode(sys::sptr<CResourceLoader>& pResourceLoader) {
    auto pTextureLoader = sys::static_pointer_cast<cym::TTextureLoader<sys::CFile>>(pResourceLoader);
    sys::CFile& rFile = pTextureLoader->getFile();
  
    CYM_LOG_NFO("cym::TCodec<CTexture,ECodec::TGA>::decode(sys::sptr<CResourceLoader>)::" << this << " FILE:" << rFile);
  
    sys::throw_if(!rFile.open(), "Cannot open TGA file!"); // + rFile.path());
  
    sys::sptr<sys::CStream>& pStream = pTextureLoader->mStream = new sys::CStream;
    
    sys::uint & rWidth  = pTextureLoader->width, 
              & rHeight = pTextureLoader->height, 
              & rSize   = pTextureLoader->size; 
    sys::ubyte& rBPP    = pTextureLoader->bpp;
    bool      & rAlpha  = pTextureLoader->alpha;
    uint      & rFlags  = pTextureLoader->flags;
    
    sys::ubyte              tHeader[18] = {0};
    
    static sys::byte tDeCompressed[12] = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    static sys::byte tIsCompressed[12] = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    
    rFile.read((byte*)(&tHeader), sizeof(tHeader));
    
    rBPP    = tHeader[16]; sys::throw_if((rBPP != 24) && (rBPP != 32), "TGA's Pixel format not supported!");
    rWidth  = tHeader[13] * 256 + tHeader[12];
    rHeight = tHeader[15] * 256 + tHeader[14];
    rSize   = ((rWidth * rBPP + 31) / 32) * 4 * rHeight;
    rAlpha  = rBPP > 24;
    rFlags |= (rBPP == 24) ? CTexture::EFlag::RGB : CTexture::EFlag::RGBA;
    
    if (!std::memcmp(tDeCompressed, &tHeader, sizeof(tDeCompressed))) {
      byte* rData {pStream->data(rSize)};
      rFile.read(rData, rSize);
    } else if (!std::memcmp(tIsCompressed, &tHeader, sizeof(tIsCompressed))) {
      // rFlags |= CTexture::EFlag::COMPRESSED;
           pixel tPixel {0};
      sys::uint  iByte  = {0};
      sys::ulong iPixel = {0};
      
      sys::ubyte nChunk = {0};
      
      uint nBytes = rBPP / 8; // 24/8 = 3 Bytes // 32/8 = 4 Bytes
      
      byte* rData {pStream->data(rWidth * rHeight * sizeof(pixel))};
      
      do {
        rFile.read((byte*)(&nChunk), sizeof(nChunk));
        // chunk size
        if (nChunk < 128) {
          ++nChunk;
          // for each pixel in chunk
          for (uint i = 0; i < nChunk; i++, iPixel++) {
            rFile.read((byte*)(&tPixel), nBytes);
            // write data
            rData[iByte++] = tPixel.b;
            rData[iByte++] = tPixel.g;
            rData[iByte++] = tPixel.r;
            if (rAlpha) rData[iByte++] = tPixel.a;
          }
        } else {
          nChunk -= 127;
          // read data
          rFile.read((byte*)(&tPixel), nBytes);
          // for each pixel in chunk
          for (uint i = 0; i < nChunk; i++, iPixel++) {
            // write data
            rData[iByte++] = tPixel.b;
            rData[iByte++] = tPixel.g;
            rData[iByte++] = tPixel.r;
            if (rAlpha) rData[iByte++] = tPixel.a;
          }
        }
      } while (iPixel < (rWidth * rHeight));
      
      
    } else {
      throw sys::exception("TGA's Data format not supported!",__FILE__,__LINE__);
    }
  }
    
  void TCodec<CTexture,ECodec::BMP>::decode(sys::sptr<CResourceLoader>& pResourceLoader) {
    auto pTextureLoader = sys::static_pointer_cast<cym::TTextureLoader<sys::CFile>>(pResourceLoader);
    sys::CFile& rFile   = pTextureLoader->getFile();
  
    CYM_LOG_NFO("cym::TCodec<CTexture,ECodec::BMP>::decode(sys::sptr<CResourceLoader>)::" << this << " FILE:" << rFile);
  
    sys::throw_if(!rFile.open(), "Cannot open BMP file!"); // + rFile.path());
  
    sys::sptr<sys::CStream>& pStream = pTextureLoader->mStream = new sys::CStream;
    
    sys::uint  &rWidth  = pTextureLoader->width, 
               &rHeight = pTextureLoader->height, 
               &rSize   = pTextureLoader->size; 
    sys::ubyte &rBPP    = pTextureLoader->bpp;
    bool       &rAlpha  = pTextureLoader->alpha;
    uint       &rFlags  = pTextureLoader->flags;
    
    sys::ulong tLength = rFile.size();
    
    std::vector<ubyte> tInfo(tLength);
    
    rFile.read((byte*)tInfo.data(), 54);
    
    sys::throw_if((tInfo[0] != 'B' && tInfo[1] != 'M'), "Not a BMP file format!");
    
    rBPP    = tInfo[28]; sys::throw_if((rBPP != 24) && (rBPP != 32), "BMP's Pixel format not supported!");
    rWidth  = tInfo[18] + (tInfo[19] << 8);
    rHeight = tInfo[22] + (tInfo[23] << 8);
    rSize   = ((rWidth * rBPP + 31) / 32) * 4 * rHeight;
    rFlags |= (rBPP == 24) ? CTexture::EFlag::BGR : CTexture::EFlag::BGRA;
    rFlags |= (rBPP == 24) ? CTexture::EFlag::RGB : CTexture::EFlag::RGBA;
    
    uint tOffset = tInfo[10] + (tInfo[11] << 8);
    
    byte* rData {pStream->data(rSize)};
    
    rFile.seek(tOffset);
    
    rFile.read(rData, rSize);
  }
  
  // model:obj ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TCodec<CModel,ECodec::OBJ>::decode(sys::sptr<CResourceLoader>& pResourceLoader) {
    auto        pModelLoader = sys::static_pointer_cast<cym::TModelLoader<sys::CFile>>(pResourceLoader);
    sys::CFile& rFile        = pModelLoader->getFile();
    
    CYM_LOG_NFO("cym::TCodec<CModel,ECodec::OBJ>::decode(CResourceData&)::" << this << " FILE:" << rFile);
    
    sys::throw_if(!rFile.open(), "Cannot open file!"); // + rFile.path());
    
    SData tData;
    
    auto& rGeometry    = pModelLoader->getGeometry();
    auto& rMeshLoaders = pModelLoader->getMeshLoaders(); 
    
    auto  rPositions = rGeometry.stream().make("positions", new cym::CPositionInput);
    auto  rTexcoords = rGeometry.stream().make("texcoords", new cym::CTexcoordInput);
    auto  rNormals   = rGeometry.stream().make("normals", new cym::CNormalInput);
    auto& rLayout    = rGeometry.layout();
    
    sys::block<glm::vec3> tPositions;
    sys::block<glm::vec2> tTexcoords;
    sys::block<glm::vec3> tNormals;
    
    sys::block<SIndex> tIndices;
    
    sys::map<sys::string, sys::sptr<CMaterialLoader>> tMaterialLoaders;
    sys::sptr<CMaterialLoader>                        tMaterialLoader;
    sys::string                                       tName;
    
    while (!rFile.eof()) {
      char* zLine = new char[1024];
      rFile.line(zLine, 1024);
      // span of the characters
      zLine += ::strspn(zLine, " \t\r\n");
      
      if(zLine[0] =='\0' || zLine[0] =='#' || zLine[0] == '\n') continue;
      assert(zLine);
      
      // CYM_LOG_NFO("cym::COBJCodec::decode(CResourceData&)::" << this << "::" << zLine);
      
      if (zLine[0] == 'v' && zLine[1] == ' ') {                             // position > v 0.191341 -0.980785 -0.038060
        zLine += 2;
        glm::vec3& p {tData.positions.next()};
        ::sscanf(zLine, "%f %f %f\n", &p.x, &p.y, &p.z);
        continue;
      } else if (zLine[0] == 'v' && zLine[1] == 't' && zLine[2] == ' ') {   // texcoord > vt 0.167958 0.500000
        zLine += 3;
        glm::vec2& t {tData.texcoords.next()};
        ::sscanf(zLine, "%f %f\n", &t.x, &t.y);
        continue;
      } else if (zLine[0] == 'v' && zLine[1] == 'n' && zLine[2] == ' ') {   // normal > vn -0.451282 0.289004 -0.844288
        zLine += 3;
        glm::vec3& n {tData.normals.next()};
        ::sscanf(zLine, "%f %f %f\n", &n.x, &n.y, &n.z);
        continue;
      } else if (zLine[0] == 'f' && zLine[1] == ' ') {                      // faces > f 75//83 79//83 76//83
        zLine += 2;
        zLine += ::strspn(zLine, " \t");
        // prepare to construct triangles
        uint psize = tData.positions.size();
        uint tsize = tData.texcoords.size();
        uint nsize = tData.normals.size();
        // read index by index
        while (!sys::isnewline(*zLine)) {
          SIndex tIndex{-1};
          // position
          tIndex.position = ::atoi(zLine);                               // converts the first index number
          tIndex.position += tIndex.position > 0 ? -1 : psize;           // fix index | zero base | negative = relative
          // move on to the next /
          zLine          += ::strcspn(zLine, "/ \t\r");                  // goto the next /
          // if a `/` get the next char
          if (zLine[0] == '/') {                                         // if / => more vertex compoents
            zLine++;
            // if / followed by / => missing texccoord
            if (zLine[0] == '/') {                                         // i//k = position + normal
              zLine++; // jump over /
              // normal
              tIndex.normal = ::atoi(zLine);
              tIndex.normal += tIndex.normal > 0 ? -1 : nsize;           // fix index | zero base | negative = relative
              zLine        += ::strcspn(zLine, "/ \t\r");
            } else {                                                     // i/j =  position + texcoord
              tIndex.texcoord = ::atoi(zLine);
              tIndex.texcoord += tIndex.texcoord > 0 ? -1 : tsize;       // fix index | zero base | negative = relative
              zLine          += ::strcspn(zLine, "/ \t\r");
              // all 3 components
              if (*zLine == '/') {                                       // i/j/k = position + texcoord + normal
                zLine++; // jump over /
                tIndex.normal = ::atoi(zLine);
                tIndex.normal += tIndex.normal > 0 ? -1 : nsize;         // fix index | zero base | negative = relative
                zLine        += ::strcspn(zLine, "/ \t\r");
              }
            }
          }
          
          // CYM_LOG_NFO("cym::COBJCodec::decode(CResourceData&)::index:p=" << tIndex.position << ",n=" << tIndex.normal << ",t=" << tIndex.texcoord);
          
          // face.push_back(index);
          tIndices.push(tIndex);                                         // push to the list of indices
          zLine += ::strspn(zLine, " \t\r");
        }
        continue;
      } else if (sys::strncmp(zLine, "mtllib", 6)) {                    // material > mtllib sphere.mtl
        // init materials
        zLine += 7;
        
        char tMatr[1024];                                              // material filename
        ::sscanf(zLine, "%s\n", tMatr);
  
        bool tDone = false;
        
        decodeMaterial(sys::string(rFile.folder()) + tMatr, tMaterialLoaders, tDone);              // path to textures folder
        
        if(!tDone) {
          tIndices.clear();                                           // for safety?
        }
        continue;
      } else if (sys::strncmp(zLine, "usemtl", 6)) {                     // material > usemtl sphere.mtl
        // remember material
        zLine += 7;
        
        // material name
        char tBuff[1024];
        ::sscanf(zLine, "%s\n", tBuff);
        sys::string tMatr(tBuff);
        
        // find and activate material
        if(tMaterialLoaders.find(tMatr) != tMaterialLoaders.end()) {
          tMaterialLoader = tMaterialLoaders[tMatr];
        }
        continue;
      } else if ((zLine[0] == 'g' || zLine[0] == 'o') && zLine[1] == ' ') { // group/object start > o Sphere
        // start building the mesh when u see the start of a new one
        if (!tIndices.empty()) {
          auto& rMeshLoader {pModelLoader->getMeshLoader(tName)};
  
          rMeshLoader->getName()  = tName;
          rMeshLoader->getRange().nStart = rLayout.count();
          
          sys::map<SIndex, uint> tCache;
          
          for (uint i = 0, j = 0; i < tIndices.size(); i++) {
      // @todo: needs fix for triangle fan // triangle fan = face vertices > 3
      
            SIndex                                        tIndex = tIndices[i];
            const sys::CMap<SIndex, uint>::const_iterator it     = tCache.find(tIndex);
            
            if (it == tCache.end()) {
              rPositions.push(tData.positions[tIndex.position]);   // position
            
              if (tIndex.texcoord > -1)
                rTexcoords.push(tData.texcoords[tIndex.texcoord]); // texcoord
                
              if (tIndex.normal > -1)
                rNormals.push(tData.normals[tIndex.normal]);       // normal
              
              tCache[tIndex] = j;                                  // remember this vertex
              rLayout.push(j);
              j++;
            } else {
              rLayout.push(it->second);
            }
          }
  
          rMeshLoader->getRange().nEnd = rLayout.count();
          rMeshLoader->getMaterialLoader() = tMaterialLoader;
      
          tIndices.clear();
        }
        
        // advance
        zLine += 2;
        
        // new mesh, new name
        char tBuff[1024];
        ::sscanf(zLine, "%s", tBuff);
        tName = tBuff;
        
        continue;
      }
      // clean up
      delete [] zLine;
    }
    
    if (!tIndices.empty()) {
      auto& rMeshLoader {rMeshLoaders[tName]};
    
      rMeshLoader->getName()  = tName;
      rMeshLoader->getRange().nStart = rGeometry.layout().size();
      
      sys::map<SIndex, uint> tCache;
      
      for (uint i = 0, j = 0; i < tIndices.size(); i++) {
  // @todo: needs fix for triangle fan // triangle fan = face vertices > 3
  
        SIndex                                        tIndex = tIndices[i];
        const sys::CMap<SIndex, uint>::const_iterator it     = tCache.find(tIndex);
        
        if (it == tCache.end()) {
          rPositions.push(tData.positions[tIndex.position]);   // position
        
          if (tIndex.texcoord > -1)
            rTexcoords.push(tData.texcoords[tIndex.texcoord]); // texcoord
            
          if (tIndex.normal > -1)
            rNormals.push(tData.normals[tIndex.normal]);       // normal
          
          tCache[tIndex] = j;                                  // remember this vertex
          rLayout.push(j);
          j++;
        } else {
          rLayout.push(it->second);
        }
      }
    
      rMeshLoader->getRange().nEnd = rGeometry.layout().size();
      rMeshLoader->getMaterialLoader() = tMaterialLoader;
    
      tIndices.clear();
    }
    
    
// @todo: MUST compute tangent + binormal

// @todo: MUST joints + weights : only 1 joint (root) if none are defined
    
    // CYM_LOG_NFO("cym::COBJCodec::decode(CResourceData&)::" << this <<" DONE");
    
    // sys::block<CVertex> vertices {numVertices};
    // for index in indices
      // vertices[i].position = position[index];
      // vertices[i].normal   = normal[index];
      // vertices[i].texcoord = texcoord[index];
  }
  
  void TCodec<CModel,ECodec::OBJ>::decodeMaterial(const sys::string& tFile, sys::map<sys::string, sys::sptr<CMaterialLoader>>& tMaterialLoaders, bool& tDone) {
    CYM_LOG_NFO("cym::TCodec<CModel,ECodec::OBJ>::decodeMaterial(...)::" << "FILE:" << tFile);
    
    tMaterialLoaders.clear();                                                                 // unload prev loaded .mtl files
    
    // @todo: replace w/ sys::CFile
    std::fstream fs(tFile.c_str(), std::ios::in | std::ios::binary);
    
    if (fs.fail()) {
      log::err << "cym::COBJCodec::decodeMaterial(...)" << " failed to init " << tFile << " file" << log::end;
      return;
    }
    
    sys::sptr<CMaterialLoader> tMaterialLoader;
    
    char* zLine = new char[2048];
    while(fs.peek() != -1) {
      fs.getline(zLine, 2048);
  
      zLine += ::strspn(zLine, " \t");
      if (zLine[0] == '\0' || zLine[0] == '#' || zLine[0] == '\n') 
        continue;
      assert(zLine);
      
      // CYM_LOG_NFO("cym::COBJCodec::decodeMaterial(...)::" << zLine);
      
      if (sys::strncmp(zLine, "newmtl", 6)) {
        // std::cout << line << std::endl;
        zLine += 7;
        char tBuff[1024];
        ::sscanf(zLine, "%s", tBuff);
        std::string tMatr(tBuff);
  
        // tMaterialLoaders.insert(std::pair<sys::string, sys::sptr<CMaterialLoader>>{tMatr, tMatr}});
        tMaterialLoader = tMaterialLoaders[tMatr] = new CMaterialLoader{tMatr};
        
        continue;
      } else if (sys::strncmp(zLine, "Ka", 2)) {
        zLine += 3;
        auto& tColor {tMaterialLoader->getChannelLoader(cym::CChannel::AMBIENT)->getColor()};
        ::sscanf(zLine, "%f %f %f\n", &tColor.r, &tColor.g, &tColor.b);
        continue;
        continue;
      } else if (sys::strncmp(zLine, "Kd", 2)) {
        zLine += 3;
        auto& tColor {tMaterialLoader->getChannelLoader(cym::CChannel::DIFFUSE)->getColor()};
        ::sscanf(zLine, "%f %f %f\n", &tColor.r, &tColor.g, &tColor.b);
        continue;
      } else if (sys::strncmp(zLine, "Ks", 2)) {
        zLine += 3;
        auto& tColor {tMaterialLoader->getChannelLoader(cym::CChannel::SPECULAR)->getColor()};
        ::sscanf(zLine, "%f %f %f\n", &tColor.r, &tColor.g, &tColor.b);
        continue;
      } else if (sys::strncmp(zLine, "Kt", 2)) {
        zLine += 3;
        auto& tColor {tMaterialLoader->getChannelLoader(cym::CChannel::TRANSPARENCY)->getColor()};
        ::sscanf(zLine, "%f %f %f\n", &tColor.r, &tColor.g, &tColor.b);
        continue;
      } else if (sys::strncmp(zLine, "Ke", 2)) {
        zLine += 3;
        auto& tColor {tMaterialLoader->getChannelLoader(cym::CChannel::EMISSION)->getColor()};
        ::sscanf(zLine, "%f %f %f\n", &tColor.r, &tColor.g, &tColor.b);
        continue;
      } else if (sys::strncmp(zLine, "Ni", 2)) {
        zLine += 3;
        auto& tLevel {tMaterialLoader->getChannelLoader(cym::CChannel::REFRCTION)->getLevel()};
        ::sscanf(zLine, "%f", &tLevel);
        continue;
      } else if (sys::strncmp(zLine, "Ns", 2)) {
        zLine += 3;
        auto& tLevel {tMaterialLoader->getChannelLoader(cym::CChannel::SPECULAR)->getLevel()};
        ::sscanf(zLine, "%f", &tLevel);
        continue;
      } else if (sys::strncmp(zLine, "map_Ka", 6)) {
        zLine += 7;
        tMaterialLoader->getChannelLoader(cym::CChannel::AMBIENT)->setTextureLoader(new cym::TTextureLoader<sys::CFile>{zLine});
        continue;
      } else if (sys::strncmp(zLine, "map_Kd", 6)) {
        zLine += 7;
        tMaterialLoader->getChannelLoader(cym::CChannel::DIFFUSE)->setTextureLoader(new cym::TTextureLoader<sys::CFile>{zLine});
        continue;
      } else if (sys::strncmp(zLine, "map_Ks", 6)) {
        zLine += 7;
        tMaterialLoader->getChannelLoader(cym::CChannel::SPECULAR)->setTextureLoader(new cym::TTextureLoader<sys::CFile>{zLine});
        continue;
      } else if (sys::strncmp(zLine, "map_Ns", 6)) {
        zLine += 7;
        tMaterialLoader->getChannelLoader(cym::CChannel::NORMAL)->setTextureLoader(new cym::TTextureLoader<sys::CFile>{zLine});
        continue;
      } else {
        char* ptr;
        ptr = ::strtok(zLine, " ");
        if (ptr != nullptr) {
          std::string key(ptr);
          std::string value;
          ptr = ::strtok(nullptr, " ");
          if(ptr != nullptr)
            tMaterialLoader->addUnknown(key, ptr);
          else
            tMaterialLoader->addUnknown(key, "true");
        }
      }
    }
  
    // CYM_LOG_NFO("cym::COBJCodec::decodeMaterial(...)::" << "DONE");
    tDone = true;
  }
  
  inline bool operator<(const TCodec<CModel,ECodec::OBJ>::SIndex& lhs, const TCodec<CModel,ECodec::OBJ>::SIndex& rhs) {      // for map
    if      (lhs.position != rhs.position) return lhs.position < rhs.position;
    else if (lhs.texcoord != rhs.texcoord) return lhs.texcoord < rhs.texcoord;
    else if (lhs.normal   != rhs.normal)   return lhs.normal   < rhs.normal;
    return false;
  }
  
  // model:fxb ///////////////////////////////////////////////////////////////////////////////////////////////////////

// @todo: do a fxb (3dsmax) codec/importer
  
  // model:dae ///////////////////////////////////////////////////////////////////////////////////////////////////////
 
  void TCodec<CModel,ECodec::DAE>::decode(sys::sptr<CResourceLoader>& pResourceLoader) {
    auto        pModelLoader = sys::static_pointer_cast<cym::TModelLoader<sys::CFile>>(pResourceLoader);
    sys::CFile& rFile        = pModelLoader->getFile();
    
    CYM_LOG_NFO("cym::TCodec<CModel,ECodec::DAE>::decode(sys::sptr<CResourceLoader>)::" << this << " FILE:" << rFile);
    
    sys::throw_if(!rFile.open(), "Cannot open file!"); // + rFile.path());
    
    auto& rGeometry = pModelLoader->getGeometry(); 
    auto& rLayout   = rGeometry.layout();
    auto& rStream   = rGeometry.stream();
    
    sys::CXMLParser tParser;
    
    sys::CXMLParser::STree* tTree = tParser.parse(rFile);
    
    const auto& tGeometries = (*tTree)["library_geometries"];
    
    if (pModelLoader->hasFlag(EOption::VERTICES)) {
      // CYM_LOG_NFO("cym::CDAECodec::decode(sys::sptr<CResourceLoader>)::geometry:start" );
      
      uint iLastIndex {0};
      
      for (const auto& tGeometry : tGeometries->findByName("geometry")) {
      // <library_geometries>
        // <geometry> #geometry1
          // <mesh>
            // <source>
              // <float_array count="192">                                // 192 / 3(the, xyz in accessor) = 64
              // <technique_common>
                // <accessor count=64>                                    // should MATCH vertex count in geometry
                  // <param x>
                  // <param y>
                  // <param z>
        
        // Z and Y should be swapped
        
        auto  sMesh       = tGeometry->attribute("name")->toString();
        auto& pMeshLoader = pModelLoader->getMeshLoader(sMesh);
  
        pMeshLoader->getName() = sMesh;
        pMeshLoader->getRange().nStart = rLayout.count();
        
        const auto& tMesh = (*tGeometry)["mesh"];
        
        const auto tTriangles = (*tMesh)["triangles"];
        const auto tPolylist  = (*tMesh)["polylist"];
        const auto tVertices  = (*tMesh)["vertices"];
        if (tTriangles != nullptr) {
          std::map<std::string, std::vector<float>> hSources;
          std::map<std::string, uint>               hStrides;
          
          {
            for (auto& tInput : tMesh->findByName("input")) {
              auto tSource = tInput->attribute("source")->ref;
              if (tSource->name == "source") {
                auto  tSemantic   = tInput->attribute("semantic");
                auto  tFloatArray = tSource->child("float_array");
                auto  tAccessor   = tSource->findOneByName("accessor");
                auto  nCount      = tAccessor->attribute("count")->toInt();
                auto  nStride     = tAccessor->attribute("stride")->toInt();
                auto  tStream     = tFloatArray->text.toStream();
                float tValue;
        
                hStrides[tSemantic->toString()] = nStride;
        
                auto& aFloats = hSources[tSemantic->toString()];
                aFloats.reserve(nCount * nStride);
                while (tStream >> tValue)
                  aFloats.push_back(tValue);
        
                if ((*tSemantic == "POSITION") && (nullptr == rStream.find("POSITION")))
                  rStream.make("POSITION", new cym::CPositionInput);
                else if ((*tSemantic == "NORMAL") && (nullptr == rStream.find("NORMAL")))
                  rStream.make("NORMAL", new cym::CNormalInput);
                else if ((*tSemantic == "TEXCOORD") && (nullptr == rStream.find("TEXCOORD")))
                  rStream.make("TEXCOORD", new cym::CTexcoordInput);
              }
            }
          }
          
          const auto&                           tInputs = tTriangles->findByName("input");
          const uint                            nInputs = tInputs.size();
          std::unordered_map<std::string, uint> hInputs;
            
          {
            for (auto&& tInput : tInputs) {
              uint nOffset   = tInput->attribute("offset")->toInt();
              auto tSemantic = tInput->attribute("semantic");
              if (*tSemantic == "VERTEX") {
                for (auto& tTemp : tVertices->findByName("input")) {
                  hInputs[tTemp->attribute("semantic")->toString()] = nOffset;
                }
              } else {
                hInputs[tSemantic->toString()] = nOffset;
              }
            }
          }
          
          const uint nTriangles = tTriangles->attribute("count")->toInt(); // triangle count 
          const uint nVertices {3};                                        // vertices per poly (triangle)
          const auto& tP = (*tTriangles)["p"]; // indices
          std::vector<uint> aP; 
          aP.reserve(nTriangles * nVertices * tTriangles->countByName("input")); // triangles * vertices * no_of_inputs_inside_triangles
          
          {
            auto tStream = tP->text.toStream();
            int i;
            while (tStream >> i)
              aP.push_back(i);
          } // count vertex component poly...
          
          {
            std::map<std::string,uint> tCache;
            uint                       z {iLastIndex};
            std::string                tToken;
            float                      fSwap;
  
            // for each triangle
            for (uint iTriangle = 0; iTriangle < nTriangles; iTriangle++) {
              const uint nOffset = iTriangle * nVertices * nInputs;
              // for each index in triangle
              for (uint iVertex = 0; iVertex < nVertices; iVertex++) {
                // clear token
                tToken.clear();
                for (auto&& [sSemantic, iInput] : hInputs) {
                  // 1 2 3   1 6 4   2 9 0 // 
                  uint p = nOffset + iVertex * nInputs + iInput; // + offset/iInput
                  uint c = aP[p]; // which component inside coresponding aFloats 
                  // add to token
                  tToken.append(std::to_string(c));
                }
                
                // cache the token + current index(for ibo) 
                auto it = tCache.find(tToken);
                if (it == tCache.end()) {
                  // for each vertex input/component : position/normal/texcoord
                  for (auto&& [sSemantic, iInput] : hInputs) {
                    uint p = nOffset + iVertex * nInputs + iInput;
                    uint c = aP[p]; // which component inside coresponding aFloats 
                    
                    const auto& nStride = hStrides[sSemantic];
                    const auto& fFloats = hSources[sSemantic];
                    
                    // extract each component field (xyz,st,uv,rgb)
                    float fVec[nStride];
                    for (uint iFloat = 0; iFloat < nStride; iFloat++) {
                      fVec[iFloat] = fFloats[nStride * c + iFloat];
                    }
                    
                    // swap y & z
                    if (sSemantic.compare("POSITION") == 0) {
                      fSwap   = fVec[1];
                      fVec[1] = fVec[2];
                      fVec[2] = fSwap;
                    }
                    
                    // add position/normal/texcoord
                    rStream[sSemantic]->push(&fVec);
                  }
                  
                  // cache
                  tCache[tToken] = z;
                  // add to indices
                  rLayout.push(z);
                  // next
                  z++;
                  // last/biggest index
                  iLastIndex = glm::max(iLastIndex,z);
                } else {
                  rLayout.push(it->second);
                }
              }
            }
          }
          
          // mesh range
          pMeshLoader->getRange().nEnd = rLayout.count();
          // done
        } else if (tPolylist != nullptr) {
          const auto tInputs    = (*tPolylist).findByName("input");
          const uint nInputs    = tInputs.size();
          
          std::map<std::string, std::vector<float>> hSources;
          std::map<std::string, uint>               hStrides;
          
          {
            for (auto& tInput : tInputs) {
              auto tSemantic = tInput->attribute("semantic");
              
              bool bVertex   = *tSemantic == "VERTEX";
              auto tSource   = bVertex ? tInput->attribute("source")->ref->child("input")->attribute("source")->ref 
                                       : tInput->attribute("source")->ref;
              
              auto        tFloatArray = tSource->child("float_array");
              auto        tAccessor   = tSource->findOneByName("accessor");
              auto        nCount      = tAccessor->attribute("count")->toInt();
              auto        nStride     = tAccessor->attribute("stride")->toInt();
              auto        tStream     = tFloatArray->text.toStream();
              float       tValue;
              
              auto& aFloats = hSources[tSemantic->toString()];
              hStrides[tSemantic->toString()] = nStride;
              
              aFloats.reserve(nCount*nStride);
              while (tStream >> tValue) 
                aFloats.push_back(tValue);
              
              if ((*tSemantic == "VERTEX") && (nullptr == rStream.find("VERTEX")))
                rStream.make("VERTEX", new cym::CPositionInput);
              else if ((*tSemantic == "NORMAL") && (nullptr == rStream.find("NORMAL")))
                rStream.make("NORMAL", new cym::CNormalInput);
              else if ((*tSemantic == "TEXCOORD") && (nullptr == rStream.find("TEXCOORD")))
                rStream.make("TEXCOORD", new cym::CTexcoordInput);
            //else
              //throw sys::exception(tSemantic->toString() + " is NOT SUPPORTED!",__FILE__,__LINE__);
            }
          }
          
          const uint nPolys = tPolylist->attribute("count")->toInt();
          const auto& tVcount = (*tPolylist)["vcount"]; // read all numbers
          int         aVcount[nPolys];
          
          uint        nP = 0;
          uint        nIndices {0};
          
          std::unordered_map<std::string, std::pair<uint,bool>> hInputs;
          
          {
            for (auto& tInput : tInputs) {
              auto tSemantic = tInput->attribute("semantic");
              bool bVertex = *tSemantic == "VERTEX";
              auto tSource = bVertex ? tInput->attribute("source")->ref->child("input")->attribute("source")->ref : tInput->attribute("source")->ref;
              hInputs[tSemantic->toString()]/*o*/= {tInput->attribute("offset")->toInt(), bVertex};
            }
            
            auto tStream = tVcount->text.toStream();
            int  tValue, n {0};
            while (tStream >> tValue) {
              aVcount[n++] = tValue;
              nP += tValue * nInputs;
              nIndices += (tValue-2)*3;
            }
          }
          
          const auto& tP = (*tPolylist)["p"]; // p count = sum(vcount) * nInputs
          int aP[nP];
          
          {
            auto tStream = tP->text.toStream();
            int i, j {0};
            while (tStream >> i)
              aP[j++] = i;
          } // count vertex component poly...
          
          {
            std::map<std::string,uint> tCache;
            uint                       z {iLastIndex};
            std::string                tToken;
            float                      fSwap;
            
            for (uint iPoly = 0; iPoly < nPolys; iPoly++) { // 6x4
              const auto& nVertices = aVcount[iPoly];
              // for each triangle
              for (uint iTriangle = 0, nTriangles = nVertices - 2; iTriangle < nTriangles; iTriangle++) { // 0 1   // t = triangles
                // for each index in triangle
                for (uint j = iTriangle; j < 3 + iTriangle; j++) {        // v = vertices per triangles 
                  // 4 vertices = 2 triangles = 0 1 2 + 0 2 3
                  uint iVertex = iTriangle == j ? 0 : j;
                  uint nOffset = iPoly * nVertices * nInputs + 3 * nTriangles * iVertex; // march until offset
                  
                  // clear token
                  tToken.clear();
                  
                  // read each polylist index into a token, needed for creating geometry index/ibo
                  uint h {0};
                  for (auto&& [sSemantic, tSecond] : hInputs) { // 2
                    uint p = nOffset + tSecond.first; // offset + input offset
                    uint c = aP[p]; // which component inside coresponding aFloats 
                    // add to token
                    tToken.append(std::to_string(c));
                    // next digit
                    h++;
                  }
                  
                  // cache the token + current index(for ibo) 
                  auto it = tCache.find(tToken);
                  if (it == tCache.end()) {
                    // for each vertex input/component : position/normal/texcoord
                    for (auto&& [sSemantic, tSecond] : hInputs) { // 2
                      uint p = nOffset + tSecond.first; // offset + input offset
                      uint c = aP[p]; // which component inside coresponding aFloats 
                      
                      const auto& nStride = hStrides[sSemantic];
                      const auto& fFloats = hSources[sSemantic];
                      
                      // extract each component field (xyz,st,uv,rgb)
                      float fVec[nStride];
                      for (uint f = 0; f < nStride; f++) {
                        fVec[f] = fFloats[nStride*c+f];
                      }
                      
                      // swap y & z
                      auto bVertex = tSecond.second;
                      if (bVertex) {
                        fSwap   = fVec[1];
                        fVec[1] = fVec[2];
                        fVec[2] = fSwap;
                      }
                      
                      // add position/normal/texcoord
                      rStream[sSemantic]->push(&fVec);
                    }
                    
                    // cache
                    tCache[tToken] = z;
                    // add to indices
                    rLayout.push(z);
                    // next
                    z++;
                    // last/biggest index
                    iLastIndex = glm::max(iLastIndex,z);
                  } else {
                    rLayout.push(it->second);
                  }
                }
              }
            }
          } // compute indices and vertices
          
          // mesh range
          pMeshLoader->getRange().nEnd = rLayout.count();
          // done
        } else {
          throw sys::exception("Triangulation mode not supported",__FILE__,__LINE__);
        }
      }
      
      // CYM_LOG_NFO("cym::CDAECodec::decode(sys::sptr<CResourceLoader>)::geometry:done" );
    }
    
  //const auto& tMaterials   = (*tTree)["library_materials"];
  //const auto& tEffects     = (*tTree)["library_effects"];
  //const auto& tControllers = (*tTree)["library_controllers"];
    const auto& tScenes      = (*tTree)["library_visual_scenes"];
    const auto& tImages      = (*tTree)["library_images"];

    if (pModelLoader->hasFlag(EOption::MATERIALS)) {
      // CYM_LOG_NFO("cym::CDAECodec::decode(sys::sptr<CResourceLoader>)::material:start" );
      
      for (const auto& tInstance : tScenes->findByName("instance_controller")) {
        const auto& tController = tInstance->attribute("url")->ref;
        const auto& tGeometry   = (*tController)["skin"]->attribute("source")->ref;
        // <library_materials>
        const auto& tMaterial   = tInstance->findOneByName("instance_material")->attribute("target")->ref;
        // <library_effects>
        const auto& tEffect     = (*tMaterial)["instance_effect"]->attribute("url")->ref;
        
        // mesh + material
              auto& pMeshLoader     = pModelLoader->getMeshLoader(tGeometry->attribute("name")->toString());
              auto& pMaterialLoader = pMeshLoader->useMaterialLoader(tMaterial->attribute("name")->toString());
  
        // @todo: there might be more instance_material then materials, like a 2 meshes w/ the same material
        
        const auto& tTechnique = tEffect->findOneByName("technique");
        const auto& tShading   = tEffect->findOneByName("technique")->children[0];
        for (const auto& tComponent : tShading->children) {
          const auto& tColor   = (*tComponent)["color"];
          const auto& tTexture = (*tComponent)["texture"];
          sys::CXMLParser::SText tFile;
          if (tTexture) {
            const auto& tSource = tEffect->findOneByAttributeValue(tTexture->attribute("texture")->value)->findOneByName("source");
            const auto& tInitFrom = tEffect->findOneByAttributeValue(tSource->text.value)->findOneByName("init_from");
            const auto& tImage = tImages->findById(tInitFrom->text.value);
            tFile  = (*tImage)["init_from"]->text;
          }
          
          if (tComponent->name == "emission") {
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::EMISSION);
            if (tColor) {
              tColor->text.toStream() >> std::pair((float*)pChannelLoader->getColor(), 4);
            }
            if (tTexture) {
              pChannelLoader->setTextureLoader(new TTextureLoader<sys::CFile>{std::string(rFile.folder()) + sys::string(tFile.value.from + 8, tFile.value.size - 8)});
            }
          } else if (tComponent->name == "diffuse") {
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::DIFFUSE);
            if (tColor){
              tColor->text.toStream() >> std::pair((float*)pChannelLoader->getColor(), 4);
            }
            if (tTexture) {
              pChannelLoader->setTextureLoader(new TTextureLoader<sys::CFile>{std::string(rFile.folder()) + sys::string(tFile.value.from + 8, tFile.value.size - 8)});
            }
          } else if (tComponent->name == "ambient") {
            
          } else if (tComponent->name == "specular") {
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::SPECULAR);
            if (tColor){
              tColor->text.toStream() >> std::pair((float*)pChannelLoader->getColor(), 4);
            }
            if (tTexture) {
              pChannelLoader->setTextureLoader(new TTextureLoader<sys::CFile>{std::string(rFile.folder()) + sys::string(tFile.value.from + 8, tFile.value.size - 8)});
            }
          } else if (tComponent->name == "transparent") { // opacity
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::TRANSPARENCY);
            if (tColor){
              tColor->text.toStream() >> std::pair((float*)pChannelLoader->getColor(), 4);
            }
          } else if (tComponent->name == "index_of_refraction") {
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::REFRCTION);
            pChannelLoader->getLevel() = (*tComponent)["float"]->text.toInt();
          } else if (tComponent->name == "shininess") {
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::SPECULAR);
            pChannelLoader->getLevel() = (*tComponent)["float"]->text.toInt();
          }
        }
        
        const auto& tExtra = (*tTechnique)["extra"];
        
        if (tExtra) for (auto& tItem : tExtra->child("technique")->children) {
          if (tItem->name == "spec_level") {
            auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::SPECULAR);
            pChannelLoader->getLevel() = tItem->text.toFloat();
          } else if (tItem->name == "bump") {
            const auto& tTexture = (*tItem)["texture"];
            sys::CXMLParser::SText tFile;
            if (tTexture) {
              const auto& tSource = tEffect->findOneByAttributeValue(tTexture->attribute("texture")->value)->findOneByName("source");
              const auto& tInitFrom = tEffect->findOneByAttributeValue(tSource->text.value)->findOneByName("init_from");
              const auto& tImage = tImages->findById(tInitFrom->text.value);
              tFile  = (*tImage)["init_from"]->text;
              
              auto pChannelLoader = pMaterialLoader->getChannelLoader(cym::CChannel::NORMAL);
              pChannelLoader->setTextureLoader(new TTextureLoader<sys::CFile>{std::string(rFile.folder()) + sys::string(tFile.value.from + 8, tFile.value.size - 8)});
            }
          }
        }
      }
      
      // CYM_LOG_NFO("cym::CDAECodec::decode(sys::sptr<CResourceLoader>)::material:done" );
    }

    if (pModelLoader->hasFlag(EOption::SKELETON)) {
      // <library_controllers>
        // <controller>
          // <skin> #geometry1
            // <bind_shape_matrix> // = 16 floats // 
            
            // <source id="skin-joints"> //:joints > 
              // <Name_array count="42">... // (here) list of named joints
              
            // <source id="bind_poses"> // poses
              // <float_array id="poses_array" count="672">... // 42 x 16 floats = 672 // pose for each join
                // <technique_common>
                  // <accessor source="#poses_array" count="15" stride="16">
              
            // <source> // weight
              // <float_array count="3273">.. // 3273 weights
            
            // <joints>
              // <input semantic="JOINT" source="#skin-joints"/>
              // <input semantic="INV_BIND_MATRIX" source="#bind_poses"/> // @see <source#bind_poses> => source:42x16
            // </joints>
            
            // <vertex_weights count="1467">                                   // should MATCH vertex count in geometry => vcount.length = 64
              // <input semantic="JOINT"  offset="0">
              // <input semantic="WEIGHT" offset="1">
              // <vcount>3 4</vcount> // 1st vert has 3 bones, 2nd vert has 4 // each vertex has "vcount" weights
              // <v>-1 0  0 1  1 2</v> // -1 = bind shape // (here) 1st vert uses weight[0] towards bind shape
                                                          //                      weight[1] towards bone 0
                                       // <v> has to bave 1467 * 42 joints
               
               // float[] weight_values = source#weight.float_array
               //                        
               // int joint_offset = vertex_weights.input.offset;   // 0 (here)
               // int weight_offset = vertex_weights.weight.offset; // 1 (here)
               //
               // int nbJoints = source#joints.float_array.count // 42
               // int nbPoints = vertex_weights.count            // 1467
               //
               // float[][] weights = new float[nbJoints][nbPoints];
               //
               // int index = 0; 
               // for (int i = 0; i < vcount.length; i++) {  // for [0,vcount.length) // (here) = [0,64)
               //   for (int j = 0; j < vcount[i]; ++j) {    // for [0,3) // this vector is influnced by 3 joints
               //     int joint_index  = v[index + joint_offset];  // index + 0 = 0 2 4
               //     int weight_index = v[index + weight_offset]; // index + 1 = 1 3 5
               //     weights[joint_index][i] = weight_values[weight_index]; // weights[v[0]] // weights[-1][0] // weight of joint -1 = bind shape
               //     index += 2;
               //   }
               // }
               // results in
               // weights = joint_1 => [vertex_1, vertex_2, vertex_3]
               //           joint_2 => [vertex_91, vertex_21]
               //           joint_3 => [vertex_77, vertex_35, vertex_13, vertex_53]
           
               
               // weights for each vertex MUST add up to 1, SO => the 3or4 weights we use MUST be NORMALIZED (0.3+0.2+0.5=1)
         
         // ignore everything after the 4th modifier/wieght
         // Or loop all weights which assigned to a bone and remove all which have less values (like 0.001)
          // or trim the lowes values first
           
        
        
      
      // <library_visual_scenes>
        // <visual_scene id="VisualSceneNode" name="rdmscene">
          // <node id="VisualSceneNode1" name="Armature" sid="Armature" type="JOINT">
            // <matrix>1 0 0 0 0 1 0.000000 0 0 -0.000000 1 0 0 0 0 1</matrix>                          // JOINT's matrix
    }
    
    if (pModelLoader->hasFlag(EOption::ANIMATIONS)) {
      // <library_animations>
        // <animation id="animation_id_related_to_a_joint">
          // <source id="...-input">
            // <float_array count=991>0 0.033 ... 33 (33sec animation)              // at time 0      // at time 0.033
          // <source id="...-output">
            // <float_array count=15856>                                            // use 1st matrix // use 2nd matrix
            // <technique_common>
              // <accessor count=991 stride=16>                                     // 991*16=15856
          // <source id="-interpolation">
            // <Name_array count=991>                                               // how frames will be interpolated
          // <channel target="joint/transfor">                                                  // which joint
          
          
        // animation
          // JointAnimation[] jointAnimations
        // JointAnimation
          // Frame[] frames
        // Frame
          // float time
          // JointTransform transform 
    }
          
// @todo: outV = sum:j=0->n((v * BindShapeMatrix) * InversBindMatrix:j * JointMatrix:j) * JointWeight:j:v) 
    

    // BindShapeMatrix = translate each vertex to move to proper correct scene position ('cause multiple objects will get stacked on origin) 

    delete tTree;
    
    // CYM_LOG_NFO("cym::CDAECodec::decode(CResourceData&)::" << this << " DONE");
  }
  
  // scene:scene (xml) ///////////////////////////////////////////////////////////////////////////////////////////////
  
  void TCodec<CScene,ECodec::SCENE>::decode(sys::sptr<CResourceLoader>& pResourceLoader) {
    auto        pSceneLoader = sys::static_pointer_cast<cym::TSceneLoader<sys::CFile>>(pResourceLoader);
    sys::CFile& rFile        = pSceneLoader->getFile();
    
    CYM_LOG_NFO("cym::TCodec<CScene,ECodec::SCENE>::decode(sys::sptr<CResourceLoader>)::" << this << " FILE:" << rFile);
    
    sys::throw_if(!rFile.open(), "Cannot open file!"); // + rFile.path());
    
    sys::CXMLParser tParser;
    
    sys::CXMLParser::STree* tTree = tParser.parse(rFile);
    
    
    
// @todo: travel xml into pSceneLoader (gets loaded by CScene::CScene(pSceneLoader) later)
    


    delete tTree;
  }
}

// Read all the node transforms (rotate, translation, scale, etc.) in the order you receive them.
// Concatenate them to a joint's local matrix.
// Take the joint's parent and multiply it with the local matrix.
// Store that as the bind matrix.
// Read the skin information.
// Store the joint's inverse bind pose matrix.
// Store the joint weights for each vertex.
// Multiply the bind matrix with the inverse bind pose matrix and transpose it, call it the skinning matrix.
// Multiply the skinning matrix with the position times the joint weight and add it to the weighted position.
// Use the weighted position to render.
