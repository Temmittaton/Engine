#shader vertex
#version 450 core

layout (location = 0) in vec4 position;

void main () {
	gl_Position = position;
};

#shader fragment
#version 450 core

// Structs
struct Ray {
	vec3 pos;
	vec3 dir;
};
struct Material {
	vec4 color;
};
struct HitInfo {
	bool didHit;
	float dist;
	vec3 hitPoint;
	vec3 normal;
	Material material;
};

struct Camera {
	vec3 pos;
	vec3 forward;
	float fov;
};
struct Sphere {
	vec3 pos;
	float rad;
	Material material;
};
struct Light {
	vec3 pos;
	float intensity;
	vec4 color;
};

// Inout Variables
layout (pixel_center_integer) in vec4 gl_FragCoord;
layout (location = 0) out vec4 color;
layout (std430, binding = 3) buffer ObjectBuffer {
	Sphere spheres [];
};
layout (std430, binding = 4) buffer LightBuffer {
	Light lights [];
};
// Variables
uniform vec2 _WindowDimensions;
uniform Camera _Camera;
const int MAX_BOUNCES = 1;
const vec4 SkyColorHorizon = vec4 (.25, 1, .25, 1);
const vec4 SkyColorZenith = vec4 (.6, .6, 1, 1);

// Methods
Ray mirror (Ray ray, vec3 normal, vec3 origin) {
	Ray _ray = Ray (origin, vec3 (0, 0, 0));

	_ray.dir = ray.dir - 2 * normal * dot (ray.dir, normal);

	return _ray;
}

vec4 GetEnvironmentLight (Ray ray) {
	float skyGradientT = smoothstep (0.0, 0.4, ray.dir.y);
	vec4 skyGradient = mix (SkyColorHorizon, SkyColorZenith, skyGradientT);
	// To make

	return skyGradient;
}

HitInfo SphereHit (Sphere sphere, Ray ray) {
	HitInfo _hit = HitInfo (false, 0, vec3 (0, 0, 0), vec3 (0, 0, 0), Material (vec4 (0, 0, 0, 1)));
	vec3 offsetRayPos = (ray.pos - sphere.pos);

	float a = dot (ray.dir, ray.dir);
	float b = 2 * dot (offsetRayPos, ray.dir);
	float c = dot (offsetRayPos, offsetRayPos) - sphere.rad * sphere.rad;
	float delta = b * b - 4 * a * c;

	if (delta >= 0) {
		float dist = (-b - sqrt (delta)) / (2 * a);

		if (dist >= 0) {
			_hit.didHit = true;
			_hit.dist = dist;
			_hit.hitPoint = ray.pos + ray.dir * dist;
			_hit.normal = normalize (_hit.hitPoint - sphere.pos);
			_hit.material = sphere.material;
		}
	}

	return _hit;
}

vec4 GetLight (vec3 hitPoint) {

	// To make

	return vec4 (1, 1, 1, 1);
}

vec4 GetColor (Ray ray) {
	vec4 _lights [MAX_BOUNCES];
	Material _materials [MAX_BOUNCES];
	vec4 _color = vec4 (0, 0, 0, 1);
	int i = 0;

	while (i < MAX_BOUNCES) {
		float maxDist = 0;
		HitInfo hit;

		for (int j = 0; j < spheres.length (); j++) {
			HitInfo _hit = SphereHit (spheres [j], ray);
			if (_hit.dist > maxDist) {
				return vec4 (1, 0, 0, 1); // Test
				maxDist = _hit.dist;
				hit = _hit;
			}
			return vec4 (1, 0, 0, 1); // To remove
		}
		//HitInfo _hit = SphereHit (spheres [0], ray);

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
		_color += _lights [i] * _materials [i].color;

		i--;
	}

	return _color;
}

// Main
void main () {
	vec2 uv = 2 * vec2 (gl_FragCoord.x / _WindowDimensions.x, gl_FragCoord.y / _WindowDimensions.y) - 1;

	Ray _ray = Ray (vec3 (0, 0, -5), vec3 (uv.x * 16, uv.y * 9, 1));
	//Ray _ray = Ray (vec3 (0, 0, -5), vec3 (0, 0, 1));

	color = clamp (GetColor (_ray), 0, 1);
};
