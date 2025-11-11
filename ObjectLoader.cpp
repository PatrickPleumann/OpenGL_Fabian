#include "ObjectLoader.hpp"

/// <summary>
/// Loads vertex data and indices from an OBJ file using Assimp.
/// Fills the provided vectors with vertex positions, normals, texture coordinates, tangents, bitangents, and face indices.
/// </summary>
/// <param name="obj_name">Name of the Obecjt in the OBJ Folder</param>
/// <param name="a_vertecies">vector list for the vertecies to be stored in</param>
/// <param name="a_indicies">vector list for the indicies to be stored in</param>
/// <returns> Returns 0 on success or -1 if the file could not be loaded.</returns>
int ObjectLoader::LoadObjVertFromFile(std::string _objName, std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices)
{
	const C_STRUCT aiScene* tmpScene = aiImportFile(m_objFilePath.c_str(),
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace);

	if (tmpScene == nullptr) {
		std::cout << "Error in Loading Obj: " << _objName << std::endl;
		return -1;
	}

	_vertices.clear();
	//Vertices
	for (size_t i = 0; i < tmpScene->mMeshes[0]->mNumVertices; i++) {
		const aiVector3D position = tmpScene->mMeshes[0]->mVertices[i];

		_vertices.push_back(Vertex());
		_vertices[i].pos = glm::vec3(position.x, position.y, position.z);
	}

	//Normals
	if (tmpScene->mMeshes[0]->mNormals != NULL)
	{
		for (size_t i = 0; i < tmpScene->mMeshes[0]->mNumVertices; i++)
		{
			const aiVector3D normal = tmpScene->mMeshes[0]->mNormals[i];
			_vertices[i].normal = glm::vec3(normal.x, normal.y, normal.z);
		}
	}

	//Tex Coords
	if (tmpScene->mMeshes[0]->mTextureCoords != NULL)
	{
		for (size_t i = 0; i < tmpScene->mMeshes[0]->mNumVertices; i++)
		{
			const aiVector3D texCoords = tmpScene->mMeshes[0]->mTextureCoords[0][i];
			_vertices[i].uvs = glm::vec2(texCoords.x, texCoords.y);
		}
	}
	//Tangents
	if (tmpScene->mMeshes[0]->mTangents != NULL)
	{
		for (size_t i = 0; i < tmpScene->mMeshes[0]->mNumVertices; i++)
		{
			const aiVector3D tangents = tmpScene->mMeshes[0]->mTangents[i];
			_vertices[i].tangents = glm::vec3(tangents.x, tangents.y, tangents.z);
		}
	}

	//BiTangents
	if (tmpScene->mMeshes[0]->mBitangents != NULL)
	{
		for (size_t i = 0; i < tmpScene->mMeshes[0]->mNumVertices; i++)
		{
			const aiVector3D biTangents = tmpScene->mMeshes[0]->mBitangents[i];
			_vertices[i].bitangents = glm::vec3(biTangents.x, biTangents.y, biTangents.z);
		}
	}

	//Indices
	_indices.clear();
	for (size_t i = 0; i < tmpScene->mMeshes[0]->mNumFaces; i++)
	{
		const aiFace face = tmpScene->mMeshes[0]->mFaces[i];
		_indices.push_back(face.mIndices[0]);
		_indices.push_back(face.mIndices[1]);
		_indices.push_back(face.mIndices[2]);
	}
	return 0;

}
/// <summary>
/// Loads material properties from an OBJ file using Assimp and applies them to the provided Material object.
/// Retrieves ambient, diffuse, specular colors, and shininess. 
/// </summary>
/// <param name="a_matName">Material name to be loaded from the OBJ Folder</param>
/// <param name="a_material">Material where the loaded Data is being stored in</param>
/// <returns> Returns 0 on success or -1 if loading fails.</returns>
//int ObjectLoader::LoadMaterialFromFile(std::string a_matName, Material& a_material)
//{
//	const C_STRUCT aiScene* tmpScene = aiImportFile(m_objFilePath.c_str(),
//		aiProcess_Triangulate |
//		aiProcess_JoinIdenticalVertices |
//		aiProcess_FlipUVs |
//		aiProcess_CalcTangentSpace);
//
//	if (tmpScene == nullptr)
//	{
//		std::cerr << "Loading Material: " << a_matName << " failed";
//		return -1;
//	}
//
//	const C_STRUCT aiMaterial* aimateial = tmpScene->mMaterials[tmpScene->mMeshes[0]->mMaterialIndex];
//
//	aiColor4D tmpColor;
//	float tmpvalue;
//
//	if (AI_SUCCESS == aiGetMaterialColor(aimateial, AI_MATKEY_COLOR_AMBIENT, &tmpColor))
//	{
//		a_material.SetAmbient(glm::vec3(tmpColor.r, tmpColor.g, tmpColor.b));
//	}
//	else
//	{
//		std::cout << " Error fetching Ambient Color from Material Load" << std::endl;
//	}
//	if (AI_SUCCESS == aiGetMaterialColor(aimateial, AI_MATKEY_COLOR_DIFFUSE, &tmpColor))
//	{
//		a_material.SetDiffuse(glm::vec3(tmpColor.r, tmpColor.g, tmpColor.b));
//	}
//	else
//	{
//		std::cout << " Error fetching Diffuse Color from Material Load" << std::endl;
//	}
//	if (AI_SUCCESS == aiGetMaterialColor(aimateial, AI_MATKEY_COLOR_SPECULAR, &tmpColor))
//	{
//		a_material.SetSpecular(glm::vec3(tmpColor.r, tmpColor.g, tmpColor.b));
//	}
//	else
//	{
//		std::cout << " Error fetching Specular Color from Material Load" << std::endl;
//	}
//	if (AI_SUCCESS == aiGetMaterialFloat(aimateial, AI_MATKEY_SHININESS, &tmpvalue))
//	{
//		a_material.SetShininess(tmpvalue);
//	}
//	else
//	{
//		std::cout << " Error fetching Shiniess from Material Load" << std::endl;
//	}
//	return 0;
//}