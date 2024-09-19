#include "Model.hpp"
#include "../Math/Vector3.hpp"

// Model
Model::Model () {
	mesh = {false, false, 0, {Vector3 (1, 1, 1)}};
}
Model::Model (bool isLight, float intensity, Vector3 color) {
	if (isLight) {
		mesh = {false, true, 0, {Vector3 (0, 0, 0)}};
		mesh.material.light = {intensity, color};
	}
}


// Sphere
Sphere::Sphere (float irad) {
	mesh = {true, 1};
}