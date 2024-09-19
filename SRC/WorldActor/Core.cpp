#include "Core.hpp"
#include "../Math/Vector3.hpp"

// Constructors
Core::Core () {
	position = Vector3::zero;
	scale = Vector3::one;
	rotation = Vector3::zero;
}
Core::Core (Vector3 ipos, Vector3 iscale = Vector3::one, Quaternion irot = Quaternion::identity) {
	position = ipos;
	scale = iscale;
	rotation = irot;
}