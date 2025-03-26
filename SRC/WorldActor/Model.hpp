#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

class Model {
public :
	// Attributes
	vec4 color, lightIntensity;

	// Constructors
	Model ();
	Model (vec4 color);
	Model (vec4 lightIntensity, vec4 color);

	// Destructor
	~Model ();

	// Methods
	
};