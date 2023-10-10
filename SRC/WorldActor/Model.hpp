#include "../Math/Vector3.hpp"

#pragma once
struct Material {
	Vector3 color;
};
struct Mesh {
	bool isSphere;
	bool isLight;
	float sphereRadius;
	Material material;
};
struct Light {
	float intensity;
	Vector3 color;
};

class Model {
public :
	// Attributes
	Mesh mesh;
	Light light;

	// Constructors
	Model ();
	Model (bool isSphere, bool isLight, float radiusORintensity, Vector3 color);

	// Methods
	
};

class Sphere : Model {
public :
	Sphere (float irad);
};
