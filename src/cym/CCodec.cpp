#include "cym/CCodec.hpp"
#include "cym/CTexture.hpp"
#include "cym/CModel.hpp"

namespace cym {
  // textures ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PResourceData CDDSCodec::decode(const sys::CFile& oFile) {
    log::nfo << "cym::CDDSCodec::decode(CFile&)::" << this << " FILE:" << oFile << log::end;
    
    sys::throw_if(!oFile.open(), "Cannot open file!"); // + oFile.path());
    
    cym::CTextureData*        pData   {new cym::CTextureData};  
    cym::CTextureData::SInfo& oInfo   = pData->mInfo;
    sys::PStream&             pStream = pData->mStream = new sys::CStream;
    
    char ftype[4];
    oFile.read(ftype, 4);
    sys::throw_if(::strncmp(ftype,"DDS ",4) != 0, "File not of .DDS format!");
    
    SHeader oHead;
    oFile.read((byte*)(&oHead), sizeof(oHead));
    
    if(oHead.caps2 & DDS_CUBEMAP) {
      oInfo.flags |= CTexture::EFlag::CUBEMAP;
    } else if((oHead.caps2 & DDS_VOLUME) && (oHead.depth > 0)) {
      oInfo.flags |= CTexture::EFlag::VOLUME;
    } else {
      oInfo.flags |= CTexture::EFlag::PLANEMAP;
    }
    
    uint nFaces    = oInfo.flags & CTexture::EFlag::CUBEMAP ? 6 : 1;
    uint nChannels = oHead.format.fourcc == DDS_FOURCC || oHead.format.bpp == 24 ? 3 : 4;
    
    if (oHead.format.flags & DDS_FOURCC) {
      switch (oHead.format.fourcc) {
        case DDS_FOURCC_DTX1: oInfo.flags |= CTexture::EFlag::RGBA_S3TC_DXT1; break;
        case DDS_FOURCC_DTX3: oInfo.flags |= CTexture::EFlag::RGBA_S3TC_DXT3; break;
        case DDS_FOURCC_DTX5: oInfo.flags |= CTexture::EFlag::RGBA_S3TC_DXT5; break;
      }
      oInfo.flags |= CTexture::EFlag::COMPRESSED;
    } else if(oHead.format.flags == DDS_RGBA && oHead.format.bpp == 32) {
      oInfo.flags |= CTexture::EFlag::RGBA;
    } else if(oHead.format.flags == DDS_RGB && oHead.format.bpp == 32) {
      oInfo.flags |= CTexture::EFlag::RGBA;
    } else if(oHead.format.flags == DDS_RGB && oHead.format.bpp == 24) {
      oInfo.flags |= CTexture::EFlag::RGB;
    } else if(oHead.format.bpp == 8) {
      oInfo.flags |= CTexture::EFlag::LUMINANCE;
    } else {
      sys::throw_if(true, "Pixel format not supported!");
    }

    oInfo.bpp     = oHead.format.bpp;
    oInfo.width   = oHead.width;
    oInfo.height  = glm::clamp(oHead.height,1u);
    oInfo.depth   = glm::clamp(oHead.depth,1u);
    oInfo.mipmaps = glm::clamp(oHead.mipmapcount,1u);

    uint  nWidth   {0};
    uint  nHeight  {0};
    uint  nDepth   {0};
    uint& nMipmaps {oInfo.mipmaps};
    uint& nFlags   {oInfo.flags};
    for(uint i = 0; i < nFaces; i++) {
      nWidth  = oHead.width;  
      nHeight = oHead.height;
      nDepth  = oHead.depth ? oHead.depth : 1;
      for (ushort j = 0; j < nMipmaps && (nWidth || nHeight); j++) {
        oInfo.size  += cym::mapsize(nWidth, nHeight, nDepth, nChannels, nFlags);
        nWidth       = glm::clamp(nWidth >> 1);
        nHeight      = glm::clamp(nHeight >> 1);
        nDepth       = glm::clamp(nDepth >> 1);
      }
    }
    
    byte*        pBytes  {pStream->data(oInfo.size)};
    uint         nSize   {0};
    for(uint i = 0; i < nFaces; i++) {
      nWidth  = oHead.width;
      nHeight = oHead.height;
      nDepth  = oHead.depth ? oHead.depth : 1;
      for(ushort j = 0; j < nMipmaps && (nWidth || nHeight); j++) {
        nSize   = cym::mapsize(nWidth, nHeight, nDepth, nChannels, nFlags);
        oFile.read(pBytes, nSize);
        pBytes  += nSize;
        nWidth  = glm::clamp(nWidth >> 1);
        nHeight = glm::clamp(nHeight >> 1);
        nDepth  = glm::clamp(nDepth >> 1);
      }
    }
    
    return sys::static_pointer_cast<PResourceData::type>(PTextureData{pData});
  }
  
  // models //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void COBJCodec::decode(cym::CResourceInfo& rnfo) {
    cym::CFileModelInfo& info {static_cast<cym::CFileModelInfo&>(rnfo)};
    sys::CFile&          file {info.source};
    
    log::nfo << "cym::COBJCodec::decode(CFile&)::" << this << " FILE:" << file << log::end;
    
    sys::throw_if(!file.open(), "Cannot open file!"); // + oFile.path());
    
    // sys::block<float>& vertices {info.data.first};
    // sys::block<uint>&  indices  {info.data.second};
    
    sys::block<vec3_t> tPositions;
    sys::block<vec2_t> tTexcoords;
    sys::block<vec3_t> tNormals;
    
    sys::block<mesh_t>    tMeshes;
    
    sys::block<index_t>   tIndices;
    
    sys::CMap<sys::string, material_t> tMaterials;
    material_t                         tMaterial;
    sys::string                        tName;
    
    while (!file.eof()) {
      char* zLine = new char[1024];
      file.line(zLine, 1024);
      // span of the characters
      zLine += ::strspn(zLine, " \t\r\n");
      
      if(zLine[0] =='\0' || zLine[0] =='#' || zLine[0] == '\n') continue;
      assert(zLine);
      
      //log::nfo << "cym::COBJCodec::decode(CFile&)::" << this << "::" << zLine << log::end;
      
      if (zLine[0] == 'v' && zLine[1] == ' ') {                             // position > v 0.191341 -0.980785 -0.038060
        zLine += 2;
        vec3_t position;
        ::sscanf(zLine, "%f %f %f\n", &position.x, &position.y, &position.z);
        tPositions.push(position);
        continue;
      } else if (zLine[0] == 'v' && zLine[1] == 't' && zLine[2] == ' ') {   // texcoord > vt 0.167958 0.500000
        zLine += 3;
        vec2_t texcoord;
        ::sscanf(zLine, "%f %f\n", &texcoord.x, &texcoord.y);
        tTexcoords.push(texcoord);
        continue;
      } else if (zLine[0] == 'v' && zLine[1] == 'n' && zLine[2] == ' ') {   // normal > vn -0.451282 0.289004 -0.844288
        zLine += 3;
        vec3_t normal;
        ::sscanf(zLine, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
        tNormals.push(normal);
        continue;
      } else if (zLine[0] == 'f' && zLine[1] == ' ') {                      // faces > f 75//83 79//83 76//83
        zLine += 2;
        zLine += ::strspn(zLine, " \t");
        // prepare to construct triangles
        size_t psize = tPositions.size();
        size_t tsize = tTexcoords.size();
        size_t nsize = tNormals.size();
        // read index by index
        while (false == sys::isnewline(*zLine)) {
          index_t tIndex(-1);
          // position
          tIndex.position = ::atoi(zLine);                               // converts the first index number
          tIndex.position += tIndex.position > 0 ? -1 : psize;           // fix index | zero base | negative = relative
          // move on to the next /
          zLine          += ::strcspn(zLine, "/ \t\r");                  // goto the next /
          // if a `/` get the next char
          if (*zLine == '/') {                                           // if / => more vertex compoents
            zLine++;
            // if / followed by / => missing texccoord
            if (*zLine == '/') {                                         // i//k = position + normal
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
          // face.push_back(index);
          tIndices.push(tIndex);                                         // push to the list of indices
          zLine += ::strspn(zLine, " \t\r");
        }
        continue;
      } else if (sys::strncmp(zLine, "mtllib", 6)) {                    // material > mtllib sphere.mtl
        // load materials
        zLine += 7;
        
        char tMatr[1024];                                              // material filename
        ::sscanf(zLine, "%s\n", tMatr);
  
        bool tDone = false; 
        COBJCodec::_material(file.folder() + tMatr, tMaterials, tDone);              // path to textures folder
        
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
        if(tMaterials.find(tMatr) != tMaterials.end()) {
          tMaterial = tMaterials[tMatr];
        }
        continue;
      } else if ((zLine[0] == 'g' || zLine[0] == 'o') && zLine[1] == ' ') { // group/object start > o Sphere
        // start building the mesh when u see the start of a new one
        if (!tIndices.empty()) {
          COBJCodec::_mesh(tMeshes, tPositions, tTexcoords, tNormals, tIndices, tMaterial, tName);
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
      // log::nfo << "cym::COBJCodec::decode(CFile&)::" << this << "::last+mesh" << log::end;
      COBJCodec::_mesh(tMeshes, tPositions, tTexcoords, tNormals, tIndices, tMaterial, tName);
      tIndices.clear();
    }
    
    log::nfo << "cym::COBJCodec::decode(CFile&)::" << this << " DONE" << log::end;
  }
  
  void COBJCodec::_mesh(sys::block<mesh_t>& tMeshes, const sys::block<vec3_t>& tPositions, const sys::block<vec2_t>& tTexcoords, const sys::block<vec3_t>& tNormals, const sys::block<index_t>& tIndices, const material_t& material, const sys::string& tName) {
    log::nfo << "cym::COBJCodec::_mesh(...)::indices::" << tIndices.size() << log::end;
    
    mesh_t                   tMesh;
    sys::CMap<index_t, uint> tCache;
    
    for (uint i = 0, j = 0; i < tIndices.size(); i++) {
      // @TODO: needs fix for triangle fan // triangle fan = face vertices > 3
      
      index_t                                        tIndex = tIndices[i];
      const sys::CMap<index_t, uint>::const_iterator it     = tCache.find(tIndex);
      
      if (it == tCache.end()) {
        tMesh.vertices.push(tPositions[tIndex.position].x);    // position
        tMesh.vertices.push(tPositions[tIndex.position].y);
        tMesh.vertices.push(tPositions[tIndex.position].z);
        
        if (tIndex.texcoord >= 0) {
          tMesh.vertices.push(tTexcoords[tIndex.texcoord].s);  // texcoord
          tMesh.vertices.push(tTexcoords[tIndex.texcoord].t);
        }
        
        if (tIndex.normal >= 0) {
          tMesh.vertices.push(tNormals[tIndex.normal].x);      // normal
          tMesh.vertices.push(tNormals[tIndex.normal].y);
          tMesh.vertices.push(tNormals[tIndex.normal].z);
        }
        
        tCache[tIndex] = j++;                                  // remember this vertex
      }
      
      tMesh.indices.push(tCache[tIndex]);
    }
    
    tMesh.material = material;
    
    tMeshes.push(tMesh);
    
    // log::nfo << "cym::COBJCodec::_mesh(...)::" << "done" << log::end;
  }
  
  void COBJCodec::_material(const sys::string& tFile, sys::map<sys::string, material_t>& materials, bool& tDone) {
    log::nfo << "cym::COBJCodec::_material(...)::" << "FILE:" << tFile << log::end;
    
    materials.clear();                                                                 // unload prev loaded .mtl files
    
    // @todo: replace w/ sys::CFile
    std::fstream fs(tFile.c_str(), std::ios::in | std::ios::binary);
    
    if (fs.fail()) {
      log::err << "cym::COBJCodec::_material(...)" << " failed to load " << tFile << " file" << log::end;
      return;
    }
    
    material_t* material;
    
    char* line = new char[2048];
    while(fs.peek() != -1) {
      fs.getline(line, 2048);
      
      line += ::strspn(line, " \t");
      if (line[0] =='\0' || line[0] =='#' || line[0] == '\n') 
        continue;
      assert(line);
      
      // log::nfo << "cym::COBJCodec::_material(...)::" << zLine << log::end;
      
      if (sys::strncmp(line, "newmtl", 6)) {
        // std::cout << line << std::endl;
        line += 7;
        char tBuff[1024];
        ::sscanf(line, "%s", tBuff);
        std::string tMatr(tBuff);
        
        materials.insert(std::pair{tMatr, material_t{}});
        material = &materials[tMatr];
        material->name = tMatr;
        
        continue;
      } else if (sys::strncmp(line, "Ka", 2)) {
        line += 3;
        ::sscanf(line, "%f %f %f\n", &material->ambient.color.r, &material->ambient.color.g, &material->ambient.color.b);
        continue;
      } else if (sys::strncmp(line, "Kd", 2)) {
        line += 3;
        ::sscanf(line, "%f %f %f\n", &material->diffuse.color.r, &material->diffuse.color.g, &material->diffuse.color.b);
        continue;
      } else if (sys::strncmp(line, "Ks", 2)) {
        line += 3;
        ::sscanf(line, "%f %f %f\n", &material->specular.color.r, &material->specular.color.g, &material->specular.color.b);
        continue;
      } else if (sys::strncmp(line, "Kt", 2)) {
        line += 3;
        ::sscanf(line, "%f %f %f\n", &material->transmission.color.r, &material->transmission.color.g, &material->transmission.color.b);
        continue;
      } else if (sys::strncmp(line, "Ke", 2)) {
        line += 3;
        ::sscanf(line, "%f %f %f\n", &material->emission.color.r, &material->emission.color.g, &material->emission.color.b);
        continue;
      } else if (sys::strncmp(line, "Ni", 2)) {
        line += 3;
        ::sscanf(line, "%f", &material->ior);
        continue;
      } else if (sys::strncmp(line, "Ns", 2)) {
        line += 3;
        ::sscanf(line, "%f", &material->shininess);
        continue;
      } else if (sys::strncmp(line, "map_Ka", 6)) {
        line += 7;
        material->ambient.texture = line;
        continue;
      } else if (sys::strncmp(line, "map_Kd", 6)) {
        line += 7;
        material->diffuse.texture = line;
        continue;
      } else if (sys::strncmp(line, "map_Ks", 6)) {
        line += 7;
        material->specular.texture = line;
        continue;
      } else if (sys::strncmp(line, "map_Ns", 6)) {
        line += 7;
        material->normal.texture = line;
        continue;
      } else {
        char* ptr;
        ptr = ::strtok(line, " ");
        if (ptr != nullptr) {
          std::string key(ptr);
          std::string value;
          ptr = ::strtok(nullptr, " ");
          if(ptr != nullptr)
            material->unknown.insert(std::pair{key, ptr});
          else
            material->unknown.insert(std::pair{key, "true"});
        }
      }
    }
  
    tDone = true;
  }
  
  inline bool operator<(const COBJCodec::index_t& lhs, const COBJCodec::index_t& rhs) {      // for map
    if      (lhs.position != rhs.position) return lhs.position < rhs.position;
    else if (lhs.texcoord != rhs.texcoord) return lhs.texcoord < rhs.texcoord;
    else if (lhs.normal   != rhs.normal)   return lhs.normal   < rhs.normal;
    return false;
  }
}
