#shader vertex
#version 450 core

layout (location = 0) in vec4 position;

void main () {
	gl_Position = position;
};

#shader fragment
#version 450 core

#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38
#define EPSILON .0000000001
#define NULL_HIT HitInfo (false, FLT_MAX, vec4(0), vec4(0), Material (vec4(0), vec4(0)))
#define DOT2(V) dot (V,V)

// Object structs
struct Material {vec4 color, intensity;};
struct Core {vec4 position, scale;};
struct Object {int coreIndex, matIndex;};

// Shader Structs
struct Ray {
	vec4 pos;
	vec4 dir;
};
struct HitInfo {
	bool didHit;
	float dist;
	vec4 hitPoint;
	vec4 normal;
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
layout (std430, binding = 5) buffer MaterialsBuffer {
	Material materials [];
};
// Variables,
uniform vec2 _WindowDimensions;
uniform float _Time;
uniform vec4 _CameraPos;
uniform vec4 _CameraForward;
uniform vec4 _CameraValues;

uniform vec4 _SkyColorZenith;

const vec4 SkyColorHorizon = vec4 (.25, 1, .25, 1);
const int MAX_BOUNCES = 8;

// Methods
Ray mirror (Ray ray, vec4 normal, vec4 origin) {
	Ray _ray = Ray (origin, vec4 (0));

	_ray.dir = ray.dir - 2 * normal * dot (ray.dir, normal);

	return _ray;
}

vec4 GetEnvironmentLight (Ray ray) {
	float skyGradientT = smoothstep (0.0, 0.4, ray.dir.y);
	vec4 skyGradient = mix (SkyColorHorizon, _SkyColorZenith, skyGradientT);
	// To make

	return skyGradient;
}

vec4 GetLight (vec4 hitPoint, int hitID) {
	vec4 light = materials [hitID].color * materials [hitID].intensity;
	// To optimize

	return vec4 (1);
}

// Collision functions
HitInfo SphereHit (int ID, Ray ray) {
	Core sphere = cores [ID];
	HitInfo _hit = NULL_HIT;
	vec4 offsetRayPos = (ray.pos - sphere.position);

	float a = dot (ray.dir, ray.dir);
	float b = 2 * dot (offsetRayPos, ray.dir);
	float c = dot (offsetRayPos, offsetRayPos) - sphere.scale.x * sphere.scale.x;
	float delta = b * b - 4 * a * c;

	if (delta >= 0) {
		float dist = (-b - sqrt (delta)) / (2 * a);

		if (dist >= 0) {
			_hit.didHit = true;
			_hit.dist = dist;
			_hit.hitPoint = ray.pos + ray.dir * dist;
			_hit.normal = normalize (_hit.hitPoint - sphere.position);
			_hit.material = materials [ID];
		}
	}

	return _hit;
}

vec4 GetColor (Ray ray) {
	vec4 _lights [MAX_BOUNCES];
	Material _materials [MAX_BOUNCES];
	int i = 0;
	int lastHit = -1;
	int newHit = -1;

	while (i < MAX_BOUNCES) {
		float minDist = FLT_MAX;
		HitInfo hit = NULL_HIT;

		for (int j = 0; j < objects.length (); j++) {
			if (j == lastHit) {continue;}
			HitInfo _hit = SphereHit (j, ray);

			if (_hit.dist < minDist) {
				minDist = _hit.dist;
				hit = _hit;
				newHit = j;
			}
		}

		if (!hit.didHit) {
			_lights [i] = vec4 (1, 1, 1, 1);
			_materials [i] = Material (GetEnvironmentLight (ray), vec4 (1));
			i++;
			break;
		}
		else {
			lastHit = newHit;
			_lights [i] = GetLight (hit.hitPoint, lastHit); // get light all around
			_materials [i] = hit.material;
			ray.dir = normalize (ray.dir);
			ray = mirror (ray, hit.normal, hit.hitPoint + EPSILON * hit.normal); // send ray to precise location
		}

		i++;
	}

	i--;
	vec4 _color = vec4 (0, 0, 0, 1);

	while (i >= 0) {
		_color += _lights [i] * _materials [i].color / (i + 1);

		i--;
	}

	return _color;
}

// Main 
void main () {
	vec2 uv = 2 * vec2 (gl_FragCoord.x / _WindowDimensions.x, gl_FragCoord.y / _WindowDimensions.y) - 1;

	vec4 rayDir = vec4 (uv.x * 16 * _CameraValues.x, uv.y * 9 * _CameraValues.y, 1, 0);
	Ray _ray = Ray (_CameraPos, /*normalize*/ (rayDir));

	//color = materials [1].color;
	//color = cores [1].position;
	//color = vec4(uv.x, uv.y, 0, 1);
	//color = rayDir;

	color = clamp (GetColor (_ray), 0, 1);
};
