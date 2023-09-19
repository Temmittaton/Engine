#include <Vector3.hpp>

#ifndef CORE_H
#define CORE_H

class Core {
public:
	Vector3 position, scale, rotation;

	// Constructors
	Core ();
	Core (Vector3 ipos);
	Core (Vector3 ipos, Vector3 iscale, Vector3 irot);

	Vector3 forward () {
		return rotation * Vector3::forward;
	}
};

#endif