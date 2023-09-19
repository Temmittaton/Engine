#include <Vector3.hpp>

class Core {
	public :
		Vector3 position;
		Vector3 scale;
		Vector3 rotation;

		// Constructors
		Core () {
			position = Vector3::zero;
			scale = Vector3::one;
			rotation = Vector3::zero;
		}

		Core (Vector3 ipos, Vector3 iscale, Vector3 irot) {
			position = ipos;
			scale = iscale;
			rotation = irot;
		}


		Vector3 forward () {
			return rotation * Vector3::forward;
		}
};