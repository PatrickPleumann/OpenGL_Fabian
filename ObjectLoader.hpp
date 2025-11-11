//#pragma once
//#include <string>
//#include <fstream>
//#include <glad/glad.h>
//#include<vector>
//#include "Vertex.hpp"
//#include "assimp/scene.h"
//#include <assimp/postprocess.h>
//#include "assimp/cimport.h"
//#include "Image.hpp"
//#include <iostream>
//#include "Material.hpp"
//
//
//using string = std::string;
//
//const string m_filePath = ".\Shader\";
//const string m_objFilePath = ".\Obj\";
//const string m_textureFilePath = ".\Obj\";
//const string m_defaultTextureFilePath = ".\Obj\DefaultPixel.png";
//
//class ObjectLoader
//{
//public:
//    static int LoadShaderCode(string a_shaderName, string& a_vertexShaderstring, string& a_fragmentShaderstring);
//    static int LoadObjVertFromFile(string a_objName, std::vector<Vertex>& a_vertecies, std::vector<GLint>& a_indicies);
//    static int LoadMaterialFromFile(string a_matName, Material& a_material);
//
//    static int LoadDefaultCube(std::vector<Vertex>& a_vertecies, std::vector<GLint>& a_indicies);
//    static int LoadDefaultTrinagle(std::vector<Vertex>& a_vertecies, std::vector<GLint>& a_indicies);
//
//    static int LoadTextureDataFromFile(string a_filename, SDL_Surface& a_textureData);
//    static int LoadDefaultTexture(SDL_Surface& a_textureData);
//private:
//    static string ReadShaderFromFile(string a_filePath);
//
//};