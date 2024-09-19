#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.h"

#ifndef CORE_H
#define CORE_H

class Core {
public:
	Vector3 position, scale;
	Quaternion rotation;

	// Constructors
	Core ();
	Core (Vector3 ipos, Vector3 iscale = Vector3::one, Quaternion irot = Quaternion::identity);

	Vector3 forward () {
		return rotation.toVector () * Vector3::forward;
	}
};

#endif