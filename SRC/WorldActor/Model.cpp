#include "Model.hpp"

// Model
Model::Model () {
	lightIntensity = vec4 (0,0,0,0);
	color = vec4 ();
	opaqueness = 1.0f;
	roughness = 1.0f;
}
Model::Model (vec4 color) {
	lightIntensity = vec4 (0,0,0,0);
	this->color = color;
	opaqueness = 1.0f;
	roughness = 1.0f;
}
Model::Model (vec4 color, vec4 lightIntensity, float opaque, float rough) {
	this->lightIntensity = lightIntensity;
	this->color = color;
	opaqueness = opaque;
	roughness = rough;
}

Model::~Model () {}
