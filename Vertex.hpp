#pragma once
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 pos;   //koordinaten im raum
	glm::vec4 color; // rgba werte fuer die vertices    //hemilight
	glm::vec3 normal{ 0.0f,0.0f,1.0f };  // Vektor der sich im rechten Winkel zur erstellten Flaeche befindet
	glm::vec2 uvs; // Texture coords    
	glm::vec3 tangents;
	glm::vec3 bitangents;
};