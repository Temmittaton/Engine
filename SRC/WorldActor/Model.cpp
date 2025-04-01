#include "Model.hpp"

// Model
Model::Model () {
	lightIntensity = vec4 (0,0,0,0);
	color = vec4 ();
}
Model::Model (vec4 color) {
	lightIntensity = vec4 (0,0,0,0);
	this->color = color;
}
Model::Model (vec4 color, vec4 lightIntensity) {
	this->lightIntensity = lightIntensity;
	this->color = color;
}

Model::~Model () {}
