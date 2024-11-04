#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

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
	int isLight;
	Light light;

	Material () {
		this->color = vec3 (1, 1, 1);
		this->isLight = false;
		this->light = Light ();
	}
	Material (vec3 col, Light light = Light ()) {
		this->color = col;
		this->isLight = (light.intensity != 0);
		this->light = light;
	}
};
struct Mesh {
	Material material;
	vec4 vertices [3];
	unsigned int indices [3];
	int padding = 1;

	Mesh () {
		for (int i = 0; i < 3; ++i) {
			vertices [i] = vec4 (0, 0, 0, 0);
			indices [i] = 0;
		}
		material = Material (vec3 (0, 0, 0));
	}
	Mesh (vec4 (&_vertices) [3], const unsigned int (&_indices) [3], Material _mat, bool _isLight = false, Light* _light = NULL) {
		for (int i = 0; i < 3; ++i) {
			vertices [i] = _vertices [i];
			indices [i] = _indices [i];
		}
		material = _mat;
	}
	Mesh (Light light) {
		for (int i = 0; i < 3; ++i) {
			vertices [i] = vec4 (0, 0, 0, 0);
			indices [i] = 0;
		}
		material = Material (vec3 (0, 0, 0), light);
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