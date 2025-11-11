#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "assimp/scene.h"
#include <assimp/postprocess.h>
#include "assimp/cimport.h"
#include "Image.hpp"
#include <iostream>
#include "Material.hpp"





class ObjectLoader
{
public:
	//int LoadShaderProgram(std::string a_shaderName, std::string& a_vertexShaderstring, std::string& a_fragmentShaderstring);
	int LoadObjVertFromFile(std::string a_objName, std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices);
	int LoadMaterialFromFile(std::string a_matName, Material& a_material);
	const std::string m_objFilePath = { ".\\SM_Bunny01.obj" };
	const std::string m_textureFilePath = { ".\\assets\\Treebark_Normal.jpg" };

private:
	//const std::string m_defaultTextureFilePath = { ".\Obj\DefaultPixel.png" };
};