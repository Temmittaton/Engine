#include <vector>
#include "../Math/Vector3.hpp"
#include "../Math/Vector2.hpp"

#pragma once
struct Light {
	float intensity;
	Vector3 color;

	Light (float intensity = 0, Vector3 color = Vector3 (1, 1, 1)) {
		this->intensity = intensity;
		this->color = color;
	}
};
struct Material {
	Vector3 color;
	bool isLight;
	Light light;

	Material () {
		this->color = Vector3::one;
		this->isLight = false;
		this->light = Light ();
	}
	Material (Vector3 col, bool isLight = false, Light light = Light ()) {
		this->color = col;
		this->isLight = isLight;
		this->light = light;
	}
};
struct Vertex {
	Vector3 pos;
	Vector3 normal;
	Vector2 texCoords;
};
struct Mesh {
	Material material;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh () {
		vertices = std::vector<Vertex> (0);
		indices = std::vector<unsigned int> (0);
		material = Material (Vector3::zero, false, Light ());
	}
	Mesh (std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, Material _mat, bool _isLight = false, Light* _light = NULL) {
		vertices = _vertices;
		indices = _indices;
		material = _mat;
	}
	Mesh (Light light) {
		vertices = std::vector<Vertex> (0);
		indices = std::vector<unsigned int> (0);
		material = Material (Vector3::zero, true, light);
	}
};

class Model {
public :
	// Attributes
	Mesh mesh;

	// Constructors
	Model ();
	Model (bool isLight, float intensity, Vector3 color);

	// Methods
	
};

class Sphere : Model {
public :
	Sphere (float irad);

};
