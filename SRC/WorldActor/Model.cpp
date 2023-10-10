#include "Model.hpp"
#include "../Math/Vector3.hpp"

// Model
Model::Model () {
	mesh = {false, false, 0, {Vector3 (1, 1, 1)}};
}
Model::Model (bool isSphere, bool isLight, float radiusORintensity, Vector3 color) {
	if (isSphere) {
		mesh = {true, false, radiusORintensity, {color}};
	}
	else if (isLight) {
		mesh = {false, true, 0, {Vector3 (0, 0, 0)}};
		light = {radiusORintensity, color};
	}
}


// Sphere
Sphere::Sphere (float irad) {
	mesh = {true, 1};
}