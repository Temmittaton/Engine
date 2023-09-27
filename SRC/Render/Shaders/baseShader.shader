#shader vertex
#version 330 core

layout (location = 0) in vec4 position;

void main () {
	gl_Position = position;
};

#shader fragment
#version 330 core

// Structs
struct HitInfo {
	bool didHit;
	float dist;
	vec3 hitPoint;
	vec3 normal;
};

struct Camera {
	vec3 pos;
	vec3 forward;
	float fov;
};
struct Sphere {
	vec3 pos;
	float rad;
};

// Inout Variables
layout (pixel_center_integer) in vec4 gl_FragCoord;
layout (location = 0) out vec4 color;
// Variables
uniform vec2 _WindowDimensions;
uniform Camera _Camera;

void main () {
	vec2 uv = 2 * vec2(gl_FragCoord.x / _WindowDimensions.x, gl_FragCoord.y / _WindowDimensions.y) - 1;
	
	color = vec4 (uv.x, uv.y, 0, 1);
};
