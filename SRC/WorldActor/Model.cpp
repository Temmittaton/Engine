#include "Model.hpp"

// Model
Model::Model () {
	mesh = Mesh ();
}
Model::Model (bool isLight, float intensity, vec3 color) {
	if (isLight) {
		mesh = Mesh (Light (intensity, color));
	}
}