#shader vertex
#version 450 core

layout (location = 0) in vec4 position;

void main () {
	gl_Position = position;
};

#shader fragment
#version 450 core

// Object structs
struct Light {
	float intensity;
	vec3 color;
};
struct Material {
	vec3 color;
	bool isLight;
	Light light;
};
struct Mesh {
	Material material;
	vec3[32] vertices;
	int[32] indices;
};
struct Core {
	vec3 position, scale;
	mat4 rotation;
};
struct Object {
	int coreIndex;
	int meshIndex;
};
struct Camera {
	vec3 pos;
	vec3 forward;
	float fov;
};

// Shader Structs
struct Ray {
	vec3 pos;
	vec3 dir;
};
struct HitInfo {
	bool didHit;
	float dist;
	vec3 hitPoint;
	vec3 normal;
	Material material;
};

// Inout Variables
layout (pixel_center_integer) in vec4 gl_FragCoord;
layout (location = 0) out vec4 color;
layout (std430, binding = 3) buffer ObjectBuffer {
	Object objects [];
};
layout (std430, binding = 4) buffer CoreBuffer {
	Core cores [];
};
layout (std430, binding = 5) buffer MeshBuffer {
	Mesh meshes [];
};
layout (std430, binding = 6) buffer MaterialsBuffer {
	Material materials [];
};
layout (std430, binding = 7) buffer LightIndexes {
	int lightIndexes [];
};
// Variables,
uniform vec2 _WindowDimensions;
uniform float _time;
uniform Camera _Camera;

uniform vec4 _SkyColorZenith;

const vec4 SkyColorHorizon = vec4 (.25, 1, .25, 1);
const int MAX_BOUNCES = 1;

// Methods
Ray mirror (Ray ray, vec3 normal, vec3 origin) {
	Ray _ray = Ray (origin, vec3 (0, 0, 0));

	_ray.dir = ray.dir - 2 * normal * dot (ray.dir, normal);

	return _ray;
}

vec4 GetEnvironmentLight (Ray ray) {
	float skyGradientT = smoothstep (0.0, 0.4, ray.dir.y);
	vec4 skyGradient = mix (SkyColorHorizon, _SkyColorZenith * sin (_time / 360), skyGradientT);
	// To make

	return skyGradient;
}

vec4 GetLight (vec3 hitPoint) {

	// To make

	return vec4 (1, 1, 1, 1);
}


HitInfo ObjectHit (Object object, Ray ray) {
	return HitInfo (false, 0, vec3 (0, 0, 0), vec3 (0, 0, 0), Material (vec3 (0, 0, 0), false, Light (0, vec3 (0, 0, 0))));
}

vec4 GetColor (Ray ray) {
	vec4 _lights [MAX_BOUNCES];
	Material _materials [MAX_BOUNCES];
	vec4 _color = vec4 (0, 0, 0, 1);
	int i = 0;

	while (i < MAX_BOUNCES) {
		float maxDist = 0;
		HitInfo hit;

		for (int j = 0; j < objects.length (); j++) {
			HitInfo _hit = ObjectHit (objects [j], ray);
			if (_hit.dist > maxDist) {
				return vec4 (1, 0, 0, 1); // Test
				maxDist = _hit.dist;
				hit = _hit;
			}
			return vec4 (1, 0, 0, 1); // To remove
		}
		//HitInfo _hit = ObjectHit (objects [0], ray);

		if (!hit.didHit) {
			_color += GetEnvironmentLight (ray);
			break;
		}
		else {
			_lights [i] = GetLight (hit.hitPoint);
			_materials [i] = hit.material;
			ray = mirror (ray, hit.normal, hit.hitPoint);
		}

		i++;
	}

	i--;

	while (i >= 0) {
		_color += _lights [i] * vec4(_materials [i].color, 1);

		i--;
	}

	return _color;
}

// Main
void main () {
	vec2 uv = 2 * vec2 (gl_FragCoord.x / _WindowDimensions.x, gl_FragCoord.y / _WindowDimensions.y) - 1;

	Ray _ray = Ray (vec3 (0, 0, -5), vec3 (uv.x * 16, uv.y * 9, 1));
	//Ray _ray = Ray (vec3 (0, 0, -5), vec3 (0, 0, 1));

	//color = clamp (GetColor (_ray), 0, 1);

	//color = vec4(materials [objects [0].meshIndex].light.color);
	color = vec4(cores [objects [0].coreIndex].position, 1);
};
