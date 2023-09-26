#include "Model.hpp"

// Model
Model::Model () {
	mesh = {false, 0};
}


// Sphere
Sphere::Sphere (float irad) {
	mesh = {true, 1};
}