#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

class Model {
public :
	// Attributes
	vec4 color, lightIntensity;
	float roughness, opaqueness;

	// Constructors
	Model ();
	Model (vec4 color);
	Model (vec4 lightIntensity, vec4 color, float opaque = 1.0f, float rough = 1.0f);

	// Destructor
	~Model ();

	// Methods
	
};