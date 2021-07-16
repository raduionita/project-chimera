#ifndef __cym_cfont_hpp__
#define __cym_cfont_hpp__

#include "cym/cym.hpp"
#include "glm/CVector.hpp"

namespace cym {
  class CFont;
  class CCharacter;
  
  class CCharacter {
      friend class CFont;
    public:
      glm::uint x;
      glm::uint y;
      glm::real width;
      glm::real height;
      glm::uint xOffset;
      glm::uint yOffset;
      glm::uint xAdvance;
      glm::uint page;
      
      glm::vec4 uvs; // s1 t1, s2 t2
  };
  
  class CFont {
      friend class CCharacter;
  };
  
  class CParagraph {
      
  };
}

#endif //__cym_cfont_hpp__

// @todo: 

// hpp
// ///////////////////////////////////////////////////////////////////////////////
// // character descriptor
// struct BitmapCharacter
// {
//     short x;
//     short y;
//     short width;
//     short height;
//     short xOffset;
//     short yOffset;
//     short xAdvance;
//     short page;
//     Vector4 uvs;    // s1, t1, s2, t2
// 
//     BitmapCharacter() : x(0), y(0), width(0), height(0), xOffset(0), yOffset(0),
//                         xAdvance(0), page(0) {};
// };
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// class BitmapFont
// {
// public:
//     BitmapFont();
//     ~BitmapFont();
// 
//     bool loadFont(const std::string& fileName);
//     int drawText(float x, float y, const char* str);
//     int getTextWidth(const char* str);
// 
//     void setColor(float r, float g, float b, float a);
//     void setColor(const float color[4]);
//     void setColor(const Vector4& color);
//     void setScale(float x, float y);
//     void setScale(const Vector2& scale);
//     void setAngle(float z);
//     //void setAngle(float x, float y, float z);
// 
//     short getHeight() const                 { return size; }
//     short getBaseline() const               { return base; }
// 
// protected:
// 
// 
// private:
//     void parse(const char* src);
//     //void parseInfo(Tokenizer& str);
//     void parseCommon(Tokenizer& str);
//     void parsePage(Tokenizer& str);
//     void parseCharacterCount(Tokenizer& str);
//     void parseCharacter(Tokenizer& str);
//     void parseKerning(Tokenizer& str);
//     void initUVs();
// 
//     GLuint loadBitmap(const std::string& name);
// 
//     static void getFieldAndValue(const std::string& str, std::string& field, std::string& value);
//     static void getFieldAndValue(const std::string& str, std::string& field, short& value);
//     static void trimQuotes(std::string& str);
// 
//     //std::string name;
//     short size;
//     short base;
//     short bitmapWidth;
//     short bitmapHeight;
//     float bitmapWidthInv;
//     float bitmapHeightInv;
//     short characterCount;
// 
//     //short pageCount;
//     std::vector<GLuint> pages;
//     std::map<short, BitmapCharacter> characters;
//     std::map<std::pair<short, short>, short> kernings;
//     std::string path;
//     
//     static Vertex2 quadVertices[4];
//     float color[4];
//     Vector2 scale;
//     Vector3 angle;
// };
// ///////////////////////////////////////////////////////////////////////////////
// // Tokenizer.h
// // ===========
// // General purpose string tokenizer (C++ string version)
// //
// // The default delimiters are space(" "), tab(\t, \v), newline(\n),
// // carriage return(\r), and form feed(\f).
// // If you want to use different delimiters, then use setDelimiter() to override
// // the delimiters. Note that the delimiter string can hold multiple characters.
// //
// //  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// // CREATED: 2005-05-25
// // UPDATED: 2014-02-10
// ///////////////////////////////////////////////////////////////////////////////
// 
// #ifndef TOKENIZER_H
// #define TOKENIZER_H
// 
// #include <string>
// #include <vector>
// 
// // default delimiter string (space, tab, newline, carriage return, form feed)
// const std::string DEFAULT_DELIMITER = " \t\v\n\r\f";
// 
// class Tokenizer
// {
// public:
//     // ctor/dtor
//     Tokenizer();
//     Tokenizer(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
//     ~Tokenizer();
// 
//     // set string and delimiter
//     void set(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
//     void setString(const std::string& str);             // set source string only
//     void setDelimiter(const std::string& delimiter);    // set delimiter string only
// 
//     std::string next();                                 // return the next token, return "" if it ends
//     std::string rest();                                 // return all the remains, including delimiters
// 
//     std::vector<std::string> split();                   // return array of tokens from current cursor
// 
// protected:
// 
// 
// private:
//     void skipDelimiter();                               // ignore leading delimiters
//     bool isDelimiter(char c);                           // check if the current char is delimiter
// 
//     std::string buffer;                                 // input string
//     std::string token;                                  // output string
//     std::string delimiter;                              // delimiter string
//     std::string::const_iterator currPos;                // string iterator pointing the current position
// 
// };
// 
// #endif // TOKENIZER_H


// cpp
// ///////////////////////////////////////////////////////////////////////////////
// // BitmapFont.cpp
// // ==============
// //
// //  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// // CREATED: 2009-04-15
// // UPDATED: 2017-09-06
// ///////////////////////////////////////////////////////////////////////////////
// 
// #ifdef _WIN32
// #include <windows.h>    // include windows.h to avoid thousands of compile errors even though this class is not depending on Windows
// #endif
// 
// #include <iostream>
// #include <sstream>
// #include <fstream>
// #include "BitmapFont.h"
// #include "Tga.h"
// 
// // static member definition
// Vertex2 BitmapFont::quadVertices[4];
// 
// ///////////////////////////////////////////////////////////////////////////////
// // ctor
// ///////////////////////////////////////////////////////////////////////////////
// BitmapFont::BitmapFont() : size(0), base(0), bitmapWidth(0), bitmapHeight(0),
//                            bitmapWidthInv(1), bitmapHeightInv(1)
// {
//     color[0] = color[1] = color[2] = color[3] = 1.0f;
//     scale.x = scale.y = 1.0f;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // dtor
// ///////////////////////////////////////////////////////////////////////////////
// BitmapFont::~BitmapFont()
// {
//     for(size_t i = 0; i < pages.size(); ++i)
//     {
//         glDeleteTextures(1, &pages[i]);
//     }
//     pages.clear();
//     kernings.clear();
//     characters.clear();
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // read *.fnt file
// ///////////////////////////////////////////////////////////////////////////////
// bool BitmapFont::loadFont(const std::string& fileName)
// {
//     // remember directory
//     size_t found = fileName.find_last_of("/\\");
//     if(found != std::string::npos)
//         path = fileName.substr(0, found+1);
//     else
//         path = "";
//     
//     // open the file
//     std::ifstream inFile;
//     inFile.open(fileName.c_str(), std::ios::in);
//     if(!inFile.good())
//     {
//         std::cout << "[ERROR] Failed to open file, \"" << fileName << "\"." << std::endl;
//         return false;
//     }
// 
//     // compute buffer size
//     inFile.seekg(0, std::ios::end);
//     size_t bufferSize = inFile.tellg();
//     inFile.seekg(0, std::ios::beg);
// 
//     // get memory space based on image data size
//     char* buffer = new char[bufferSize + 1];
//     buffer[bufferSize] = '\0';
// 
//     // read data
//     inFile.read(buffer, bufferSize);
// 
//     // close the image file
//     inFile.close();
// 
//     // parse font file
//     parse(buffer);
// 
//     delete [] buffer;
//     return true;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // parse font file
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parse(const char* src)
// {
//     if(!src)
//         return;
// 
//     // reset members
//     for(size_t i = 0; i < pages.size(); ++i)
//     {
//         glDeleteTextures(1, &pages[i]);
//     }
//     pages.clear();
//     kernings.clear();
//     characters.clear();
// 
//     Tokenizer lines(src, "\n");
//     Tokenizer fields;
//     std::string line;
//     std::string field;
// 
//     while((line = lines.next()) != "")
//     {
//         fields.set(line);
//         field = fields.next();
// 
//         if(field == "info")
//         {
//         //    parseInfo(fields);
//         }
//         else if(field == "common")
//         {
//             parseCommon(fields);
//         }
//         else if(field == "page")
//         {
//             parsePage(fields);
//         }
//         else if(field == "chars")
//         {
//             parseCharacterCount(fields);
//         }
//         else if(field == "char")
//         {
//             parseCharacter(fields);
//         }
//         else if(field == "kerning")
//         {
//             parseKerning(fields);
//         }
//     }
// 
//     // set uvs per character
//     initUVs();
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // print text and return width of the text
// ///////////////////////////////////////////////////////////////////////////////
// int BitmapFont::drawText(float x, float y, const char* str)
// {
//     if(!str)
//         return 0;
// 
//     char chr;
//     char prevChr = 0;
//     BitmapCharacter character;
//     std::pair<short, short> kerning;
// 
//     // snap to pixel
//     int shiftX = (int)(x + 0.5f);
//     int shiftY = (int)(y + 0.5f);
// 
//     // OpenGL calls
//     glDisable(GL_LIGHTING);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 
//     glEnableClientState(GL_VERTEX_ARRAY);
//     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//     glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2), &quadVertices[0].s);
//     glVertexPointer(2, GL_FLOAT, sizeof(Vertex2), &quadVertices[0].x);
// 
//     glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//     //glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
//     glEnable(GL_COLOR_MATERIAL);
//     glColor4fv(this->color);
// 
//     glPushMatrix();
//     glTranslatef(shiftX, shiftY, 0);
//     glScalef(scale.x, scale.y, 1);
//     //glRotatef(angle.x, 1,0,0);
//     //glRotatef(angle.y, 0,1,0);
//     glRotatef(angle.z, 0,0,1);
// 
//     int cursor = 0;
//     while((chr = *str++) != '\0')
//     {
//         character = characters[(short)chr];
// 
//         // kerning
//         kerning.first = prevChr;
//         kerning.second = chr;
//         cursor += kernings[kerning];
// 
//         quadVertices[0].s = quadVertices[1].s = character.uvs[0];
//         quadVertices[0].t = quadVertices[2].t = character.uvs[1];
//         quadVertices[0].x = quadVertices[1].x = cursor + character.xOffset;
//         quadVertices[0].y = quadVertices[2].y = base - character.yOffset;
// 
//         quadVertices[3].s = quadVertices[2].s = character.uvs[2];
//         quadVertices[3].t = quadVertices[1].t = character.uvs[3];
//         quadVertices[3].x = quadVertices[2].x = quadVertices[0].x + character.width;
//         quadVertices[3].y = quadVertices[1].y = quadVertices[0].y - character.height;
// 
//         glBindTexture(GL_TEXTURE_2D, pages[character.page]);
//         glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
// 
//         // next
//         cursor += character.xAdvance;
//         prevChr = chr;
//     }
// 
//     glPopMatrix();
// 
//     glDisableClientState(GL_VERTEX_ARRAY);
//     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// 
//     glDisable(GL_BLEND);
//     glDisable(GL_COLOR_MATERIAL);
//     glEnable(GL_LIGHTING);
//     glBindTexture(GL_TEXTURE_2D, 0);
//     
//     return (int)(cursor * scale.x + 0.5f);  // return width of the current string
// }
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // compute the width of the text
// ///////////////////////////////////////////////////////////////////////////////
// int BitmapFont::getTextWidth(const char* str)
// {
//     if(!str)
//         return 0;
//     
//     char chr;
//     char prevChr = 0;
//     std::pair<short, short> kerning;
// 
//     int cursor = 0;
//     while((chr = *str++) != '\0')
//     {
//         // kerning
//         kerning.first = prevChr;
//         kerning.second = chr;
//         cursor += kernings[kerning];
//         
//         // next
//         cursor += characters[(short)chr].xAdvance;
//         prevChr = chr;
//     }
//     return (int)(cursor * scale.x + 0.5f);
// }
// 
// 
// 
// /*
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parseInfo(Tokenizer& str)
// {
//     std::string subStr;
//     std::string field;
//     std::string value;
//     std::string faceName;
// 
//     while((subStr = str.next()) != "")
//     {
//         getFieldAndValue(subStr, field, value);
//         if(field == "face")
//         {
//             faceName = value;
//             if(value.at(value.size()-1) != '\"')
//             {
//                 std::string tmpStr;
//                 do
//                 {
//                     tmpStr += " " + str.next();
//                 }
//                 while(tmpStr.find("\"") == std::string::npos);
//                 faceName += tmpStr;
//             }
//             trimQuotes(faceName);
//             this->name = faceName;
//         }
//     }
// }
// */
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parseCommon(Tokenizer& str)
// {
//     std::string subStr;
//     std::string field;
//     short value;
// 
//     while((subStr = str.next()) != "")
//     {
//         getFieldAndValue(subStr, field, value);
//         if(field == "lineHeight")
//         {
//             this->size = value;
//         }
//         else if(field == "base")
//         {
//             this->base = value;
//         }
//         else if(field == "scaleW")
//         {
//             this->bitmapWidth = value;
//             this->bitmapWidthInv = 1.0f / this->bitmapWidth;
//         }
//         else if(field == "scaleH")
//         {
//             this->bitmapHeight = value;
//             this->bitmapHeightInv = 1.0f / this->bitmapHeight;
//         }
//         //else if(field == "pages")
//         //{
//         //    this->pageCount = value;
//         //}
//     }
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parsePage(Tokenizer& str)
// {
//     std::string subStr;
//     std::string field;
//     std::string value;
//     std::string fileName;
// 
//     while((subStr = str.next()) != "")
//     {
//         getFieldAndValue(subStr, field, value);
//         if(field == "file")
//         {
//             fileName = value;
//             if(value.at(value.size()-1) != '\"')
//             {
//                 std::string tmpStr;
//                 do
//                 {
//                     tmpStr += " " + str.next();
//                 }
//                 while(tmpStr.find("\"") == std::string::npos);
//                 fileName += tmpStr;
//             }
//             trimQuotes(fileName);
//             GLuint texId = this->loadBitmap(path + fileName);
//             pages.push_back(texId);
//         }
//     }
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parseCharacterCount(Tokenizer& str)
// {
//     std::string subStr;
//     std::string field;
//     short value;
//     
//     while((subStr = str.next()) != "")
//     {
//         getFieldAndValue(subStr, field, value);
//         if(field == "count")
//         {
//             characterCount = value;
//         }
//     }
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parseCharacter(Tokenizer& str)
// {
//     std::string subStr;
//     std::string field;
//     short value;
//     short index = 0;
// 
//     while((subStr = str.next()) != "")
//     {
//         getFieldAndValue(subStr, field, value);
//         if(field == "id")
//         {
//             index = value;
//             BitmapCharacter character;
//             characters[index] = character;
//         }
//         else if(field == "x")
//         {
//             characters[index].x = value;
//         }
//         else if(field == "y")
//         {
//             characters[index].y = value;
//         }
//         else if(field == "width")
//         {
//             characters[index].width = value;
//         }
//         else if(field == "height")
//         {
//             characters[index].height = value;
//         }
//         else if(field == "xoffset")
//         {
//             characters[index].xOffset = value;
//         }
//         else if(field == "yoffset")
//         {
//             characters[index].yOffset = value;
//         }
//         else if(field == "xadvance")
//         {
//             characters[index].xAdvance = value;
//         }
//         else if(field == "page")
//         {
//             characters[index].page = value;
//         }
//     }
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::parseKerning(Tokenizer& str)
// {
//     std::string subStr;
//     std::string field;
//     short value;
//     std::pair <short, short> kerning;
// 
//     while((subStr = str.next()) != "")
//     {
//         getFieldAndValue(subStr, field, value);
//         if(field == "first")
//         {
//             kerning.first = value;
//         }
//         else if(field == "second")
//         {
//             kerning.second = value;
//         }
//         else if(field == "amount")
//         {
//             kernings[kerning] = value;
//         }
//     }
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::getFieldAndValue(const std::string& str, std::string& field, std::string& value)
// {
//     Tokenizer tokenizer(str, "=");
//     field = tokenizer.next();
//     value = tokenizer.next();
// }
// 
// void BitmapFont::getFieldAndValue(const std::string& str, std::string& field, short& value)
// {
//     std::string valueStr;
//     Tokenizer tokenizer(str, "=");
//     field = tokenizer.next();
//     valueStr = tokenizer.next();
//     std::stringstream ss(valueStr);
//     ss >> value;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // trim leading and tailing quote char
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::trimQuotes(std::string& str)
// {
//     str = str.substr(1, str.size()-2);
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // set font colour
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::setColor(float r, float g, float b, float a)
// {
//     this->color[0] = r;
//     this->color[1] = g;
//     this->color[2] = b;
//     this->color[3] = a;
// }
// 
// void BitmapFont::setColor(const float color[4])
// {
//     if(!color)
//         return;
// 
//     setColor(color[0], color[1], color[2], color[3]);
// }
// 
// void BitmapFont::setColor(const Vector4& color)
// {
//     setColor(color[0], color[1], color[2], color[3]);
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // set scale
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::setScale(float x, float y)
// {
//     scale.x = x;
//     scale.y = y;
// }
// 
// void BitmapFont::setScale(const Vector2& scale)
// {
//     this->scale = scale;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // set angle
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::setAngle(float z)
// {
//     angle.z = z;
// }
// /*
// void BitmapFont::setAngle(float x, float y, float z)
// {
//     angle.x = x;
//     angle.y = y;
//     angle.z = z;
// }
// */
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // load texture
// ///////////////////////////////////////////////////////////////////////////////
// GLuint BitmapFont::loadBitmap(const std::string& name)
// {
//     Image::Tga tga;
//     tga.read(name.c_str());
//     GLint format;
//     switch(tga.getBitCount())
//     {
//         case 8:
//             format = GL_ALPHA;
//             break;
//         case 24:
//             format = GL_RGB;
//             break;
//         case 32:
//             format = GL_RGBA;
//             break;
//     }
// 
//     // copy the texture to OpenGL
//     GLuint texture;
//     glGenTextures(1, &texture);
// 
//     // set active texture and configure it
//     glBindTexture(GL_TEXTURE_2D, texture);
// 
//     // select modulate to mix texture with color for shading
//     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
// 
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
// 
//     glTexImage2D(GL_TEXTURE_2D, 0, format, tga.getWidth(), tga.getHeight(), 0, format, GL_UNSIGNED_BYTE, tga.getDataRGB());
// 
//     glBindTexture(GL_TEXTURE_2D, 0);
// 
//     return texture;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// void BitmapFont::initUVs()
// {
//     std::map<short, BitmapCharacter>::iterator iter = characters.begin();
//     while(iter != characters.end())
//     {
//         iter->second.uvs[0] = iter->second.x * bitmapWidthInv;
//         iter->second.uvs[1] = iter->second.y * bitmapHeightInv;
//         iter->second.uvs[2] = (iter->second.x + iter->second.width) * bitmapWidthInv;
//         iter->second.uvs[3] = (iter->second.y + iter->second.height) * bitmapHeightInv;
// 
//         ++iter;
//     }
// }

// ///////////////////////////////////////////////////////////////////////////////
// // Tokenizer.cpp
// // =============
// // General purpose string tokenizer (C++ string version)
// //
// // The default delimiters are space(" "), tab(\t, \v), newline(\n),
// // carriage return(\r), and form feed(\f).
// // If you want to use different delimiters, then use setDelimiter() to override
// // the delimiters. Note that the delimiter string can hold multiple characters.
// //
// //  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// // CREATED: 2005-05-25
// // UPDATED: 2014-02-10
// ///////////////////////////////////////////////////////////////////////////////
// 
// #include "Tokenizer.h"
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // constructor
// ///////////////////////////////////////////////////////////////////////////////
// Tokenizer::Tokenizer() : buffer(""), token(""), delimiter(DEFAULT_DELIMITER)
// {
//     currPos = buffer.begin();
// }
// 
// Tokenizer::Tokenizer(const std::string& str, const std::string& delimiter) : buffer(str), token(""), delimiter(delimiter)
// {
//     currPos = buffer.begin();
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // destructor
// ///////////////////////////////////////////////////////////////////////////////
// Tokenizer::~Tokenizer()
// {
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // reset string buffer, delimiter and the currsor position
// ///////////////////////////////////////////////////////////////////////////////
// void Tokenizer::set(const std::string& str, const std::string& delimiter)
// {
//     this->buffer = str;
//     this->delimiter = delimiter;
//     this->currPos = buffer.begin();
// }
// 
// void Tokenizer::setString(const std::string& str)
// {
//     this->buffer = str;
//     this->currPos = buffer.begin();
// }
// 
// void Tokenizer::setDelimiter(const std::string& delimiter)
// {
//     this->delimiter = delimiter;
//     this->currPos = buffer.begin();
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // return the next token
// // If cannot find a token anymore, return "".
// ///////////////////////////////////////////////////////////////////////////////
// std::string Tokenizer::next()
// {
//     if(buffer.size() <= 0) return "";           // skip if buffer is empty
// 
//     token.clear();                              // reset token string
// 
//     this->skipDelimiter();                      // skip leading delimiters
// 
//     // append each char to token string until it meets delimiter
//     while(currPos != buffer.end() && !isDelimiter(*currPos))
//     {
//         token += *currPos;
//         ++currPos;
//     }
//     return token;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // return all the remain parts including delimiters from the current cursor
// ///////////////////////////////////////////////////////////////////////////////
// std::string Tokenizer::rest()
// {
//     if(buffer.size() <= 0) return "";           // skip if buffer is empty
// 
//     this->skipDelimiter();                      // skip leading delimiters
// 
//     // copy string from the curr position to the end
//     if(currPos == buffer.end())
//     {
//         token = "";
//     }
//     else
//     {
//         token = std::string(currPos, (std::string::const_iterator)buffer.end());
//         currPos = buffer.end();
//     }
//     return token;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // skip ang leading delimiters
// ///////////////////////////////////////////////////////////////////////////////
// void Tokenizer::skipDelimiter()
// {
//     while(currPos != buffer.end() && isDelimiter(*currPos))
//         ++currPos;
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // return true if the current character is delimiter
// ///////////////////////////////////////////////////////////////////////////////
// bool Tokenizer::isDelimiter(char c)
// {
//     return (delimiter.find(c) != std::string::npos);
// }
// 
// 
// 
// ///////////////////////////////////////////////////////////////////////////////
// // split the input string into multiple tokens
// // This function scans tokens from the current cursor position.
// ///////////////////////////////////////////////////////////////////////////////
// std::vector<std::string> Tokenizer::split()
// {
//     std::vector<std::string> tokens;
//     std::string token;
//     while((token = this->next()) != "")
//     {
//         tokens.push_back(token);
//     }
// 
//     return tokens;
// }










