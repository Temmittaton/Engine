#include "Core.hpp"
#include <Vector3.hpp>

Core::Core () {
	position = Vector3::zero;
	scale = Vector3::one;
	rotation = Vector3::zero;
}
Core::Core (Vector3 ipos) {
	position = ipos;
	scale = Vector3::one;
	rotation = Vector3::zero;
}
Core::Core (Vector3 ipos, Vector3 iscale, Vector3 irot) {
	position = ipos;
	scale = iscale;
	rotation = irot;
}