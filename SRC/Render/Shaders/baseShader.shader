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
#define NULL_HIT HitInfo (false, FLT_MAX, vec3(0), vec3(0), Material (vec4(0), Light (vec4(0), vec4 (0))))

// Object structs
struct Light {
	vec4 intensity;
	vec4 color;
};
struct Material {
	vec4 color;
	Light light;
};
struct Mesh {
	vec4[3] vertices;
	uint[3] indices; // multiple of three
	int padding;
	Material material;
};
struct Core {
	vec3 position, scale;
	mat4 rotation;
};
struct Object {
	int coreIndex;
	int meshIndex;
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
uniform vec3 _CameraPos;
uniform vec3 _CameraForward;
uniform vec4 _CameraValues;

uniform vec4 _SkyColorZenith;

const vec4 SkyColorHorizon = vec4 (.25, 1, .25, 1);
const int MAX_BOUNCES = 8;

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
    _hit.didHit = PointInTriangle(X, p0, p1, p2);
	if (_hit.didHit) {
		// If hit, fill hitinfo
		_hit.normal = cross (p1 - p0, p2 - p0);
		_hit.hitPoint = X;
		_hit.dist = length (X - ray.pos);
	}

	return _hit;
}

HitInfo ObjectHit (Object object, Ray ray) {
	int triangleNumber = meshes [object.meshIndex].indices.length () / 3;
	int closestHitID = -1;
	HitInfo hit = NULL_HIT;

	for (int i = 0; i < triangleNumber; i++) {
		vec4 v1 = meshes [object.meshIndex].vertices [meshes [object.meshIndex].indices [3 * i]];
		vec4 v2 = meshes [object.meshIndex].vertices [meshes [object.meshIndex].indices [3 * i + 1]];
		vec4 v3 = meshes [object.meshIndex].vertices [meshes [object.meshIndex].indices [3 * i + 2]];
		HitInfo _hit = TriangleHit (ray, v1.xyz, v2.xyz, v3.xyz);

		if (_hit.dist < hit.dist) {
			hit = _hit;
			closestHitID = i;
		}
	}
	
	return hit;
}

vec4 GetColor (Ray ray) {
	vec4 _lights [MAX_BOUNCES];
	Material _materials [MAX_BOUNCES];
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
			_lights [i] = vec4 (1, 1, 1, 1);
			_materials [i] = Material (GetEnvironmentLight (ray), Light (vec4 (0), vec4 (1)));
			i++;
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

	Ray _ray = Ray (_CameraPos, (vec3 (uv.x * 16 * _CameraValues.x, uv.y * 9 * _CameraValues.y, 1)));
	//Ray _ray = Ray (vec3 (0, 0, -5), vec3 (0, 0, 1));

	//color = vec4 (meshes [objects [0].meshIndex].material.color, 1); // texting mesh color
	//color = vec4 (cores [objects [0].coreIndex].position, 1); // testing object position
	//color = meshes [objects [0].meshIndex].vertices [2]; // testing vertices
	//color = vec4 (meshes [objects [0].meshIndex].indices [0], 0, 0, 1); // testing indexes
	//color = meshes [0].material.light.color;

	/*vec4 p0 = meshes [objects [0].meshIndex].vertices [0];
	vec4 p1 = meshes [objects [0].meshIndex].vertices [1];
	vec4 p2 = meshes [objects [0].meshIndex].vertices [2];*/
	//color = vec4 (IntersectPlane(_ray, p0.xyz, p1.xyz, p2.xyz) / 64, 1); test hit point on plane
	//HitInfo _hit = TriangleHit (_ray, p0.xyz, p1.xyz, p2.xyz);
	/*HitInfo _hit = ObjectHit (objects [0], _ray);

	if (_hit.didHit) {
		color = vec4 (1, 0, 0, 1);
	}
	else {
		color = vec4 (0, 1, 0, 1);
	}*/
	
	color = clamp (GetColor (_ray), 0, 1);
};
