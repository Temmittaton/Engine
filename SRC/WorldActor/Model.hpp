#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace glm;

#pragma once
struct Light {
	float intensity;
	vec3 color;

	Light (float intensity = 0, vec3 color = vec3 (1, 1, 1)) {
		this->intensity = intensity;
		this->color = color;
	}
};
struct Material {
	vec3 color;
	bool isLight;
	Light light;

	Material () {
		this->color = vec3 (1, 1, 1);
		this->isLight = false;
		this->light = Light ();
	}
	Material (vec3 col, bool isLight = false, Light light = Light ()) {
		this->color = col;
		this->isLight = isLight;
		this->light = light;
	}
};
struct Vertex {
	vec3 pos;
	vec3 normal;
	vec2 texCoords;
};
struct Mesh {
	Material material;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh () {
		vertices = std::vector<Vertex> (0);
		indices = std::vector<unsigned int> (0);
		material = Material (vec3 (0, 0, 0), false, Light ());
	}
	Mesh (std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, Material _mat, bool _isLight = false, Light* _light = NULL) {
		vertices = _vertices;
		indices = _indices;
		material = _mat;
	}
	Mesh (Light light) {
		vertices = std::vector<Vertex> (0);
		indices = std::vector<unsigned int> (0);
		material = Material (vec3 (0, 0, 0), true, light);
	}
};

class Model {
public :
	// Attributes
	Mesh mesh;

	// Constructors
	Model ();
	Model (bool isLight, float intensity, vec3 color);

	// Methods
	
};