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
#define NULL_HIT HitInfo (false, FLT_MAX, vec3(0), vec3(0), Material (vec3(0), false, Light (0, vec3 (0))))

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
	int[33] indices; // multiple of three
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
uniform float _Time;
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
	vec4 skyGradient = mix (SkyColorHorizon, _SkyColorZenith, skyGradientT);
	// To make

	return skyGradient;
}

vec4 GetLight (vec3 hitPoint) {

	// To make

	return vec4 (1, 1, 1, 1);
}

// Collision functions
bool PointInOrOn( vec3 P1, vec3 P2, vec3 A, vec3 B ) {
    vec3 CP1 = cross(B - A, P1 - A);
    vec3 CP2 = cross(B - A, P2 - A);
    return (dot (CP1, CP2) >= 0);
}
bool PointInTriangle( vec3 px, vec3 p0, vec3 p1, vec3 p2 ) {
    return ((PointInOrOn(px, p0, p1, p2) && PointInOrOn(px, p1, p2, p0)) && PointInOrOn(px, p2, p0, p1));
}
vec3 IntersectPlane(Ray ray, vec3 p0, vec3 p1, vec3 p2) {
    vec3 D = ray.dir;
    vec3 N = cross(p1-p0, p2-p0);
    vec3 X = ray.pos + D * dot(p0 - ray.pos, N) / dot(D, N);

    return X;
}
HitInfo TriangleHit(Ray ray, vec3 p0, vec3 p1, vec3 p2) {
	HitInfo _hit = NULL_HIT;

    vec3 X = IntersectPlane(ray, p0, p1, p2);
    _hit.didHit =  PointInTriangle(X, p0, p1, p2);
	if (_hit.didHit) {
		// If hit, fill hitinfo
		_hit.normal = cross (p1 - p0, p2 - p0);
		_hit.hitPoint = X;
	}

	return _hit;
}

HitInfo ObjectHit (Object object, Ray ray) {
	int triangleNumber = meshes [object.meshIndex].indices.length () / 3;
	int closestHitID = -1;
	HitInfo hit = NULL_HIT;

	for (int i = 0; i < triangleNumber; i += 3) {
		vec3 v1 = meshes [object.meshIndex].vertices [meshes [object.meshIndex].indices [triangleNumber]];
		vec3 v2 = meshes [object.meshIndex].vertices [meshes [object.meshIndex].indices [triangleNumber + 1]];
		vec3 v3 = meshes [object.meshIndex].vertices [meshes [object.meshIndex].indices [triangleNumber + 2]];
		HitInfo _hit = TriangleHit (ray, v1, v2, v3);

		if ((_hit.didHit) && (_hit.dist < hit.dist)) {
			hit = _hit;
			closestHitID = i;
		}
	}
	
	return hit;
}

vec4 GetColor (Ray ray) {
	vec4 _lights [MAX_BOUNCES];
	Material _materials [MAX_BOUNCES];
	vec4 _color = vec4 (0, 0, 0, 1);
	int i = 0;

	while (i < MAX_BOUNCES) {
		float minDist = FLT_MAX;
		HitInfo hit;

		for (int j = 0; j < objects.length (); j++) {
			HitInfo _hit = ObjectHit (objects [j], ray);

			if (_hit.dist < minDist) {
				minDist = _hit.dist;
				hit = _hit;

				hit.material = meshes [objects [j].meshIndex].material;
			}
		}

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

	float fov = 90 + 80 * sin (_Time);
	fov /= 90;

	Ray _ray = Ray (vec3 (0, 0, -5), vec3 (uv.x * 16 * fov, uv.y * 9, 1));
	//Ray _ray = Ray (vec3 (0, 0, -5), vec3 (0, 0, 1));

	color = clamp (GetColor (_ray), 0, 1);
};
