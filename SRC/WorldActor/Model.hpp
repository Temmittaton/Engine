#include <vector>
#include "../Math/tiny_obj_loader.h"
#include "../Math/Vector3.hpp"

#pragma once
class Model {
public :
	// Attributes
	Mesh mesh;

	// Constructors

	// Methods
	
};

class Sphere : Model {
public :
	Sphere (float irad);
};

struct Mesh {
	bool isSphere;
	float sphereRadius;
};