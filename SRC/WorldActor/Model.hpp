#include <vector>
#include "../Math/Vector3.hpp"

#pragma once

struct Mesh {
	bool isSphere;
	float sphereRadius;
};

class Model {
public :
	// Attributes
	Mesh mesh;

	// Constructors
	Model ();

	// Methods
	
};

class Sphere : Model {
public :
	Sphere (float irad);
};
