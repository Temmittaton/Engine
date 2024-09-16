#ifndef _Vector2_h_
#define _Vector2_h_

#include <iostream>
#include <math.h>

class Vector2 {
public:
	//constructors
	constexpr Vector2 (float ix, float iy) : data {ix, iy} {}
	constexpr Vector2 (float ia) : data {ia, ia} {}
	constexpr Vector2 () : data {0} {}

	//variables
	float data [2];

	//operators
	float operator[](unsigned int index) const {
		return data [index];
	}
	float& operator[](unsigned int index) {
		return data [index];
	}
	Vector2 operator+(const Vector2& right) const;
	Vector2 operator-(const Vector2& right) const;
	Vector2 operator-() const { return Vector2 (-data [0], -data [1]); };
	Vector2 operator*(const Vector2& right) const;
	Vector2 operator/(const Vector2& right) const;
	Vector2& operator+=(const Vector2& right);
	Vector2& operator-=(const Vector2& right);
	Vector2& operator*=(const Vector2& right);
	Vector2& operator/=(const Vector2& right);

	//functions
	void normalize ();
	Vector2 normalized () const;
	float absolute () const;
	float absolute2 () const; // Squared variant
	bool isZero () const { return data [0] == 0 && data [1] == 0; }
	static float dotProduct (const Vector2& left, const Vector2& right);
	float angleBetweenVectors (const Vector2& otherVector) const;
	/**
	 * @brief      Rotate this vector using another vector as rotation axis.
	 *
	 * @param[in]  v         Vector used as rotations axis. Needs to be
	 *                       normalized
	 * @param[in]  rotation  The rotation angle in radians.
	 */
	void rotateArroundVector (const Vector2& v, float rotation);

	// Constants
	static const Vector2 forward;
	static const Vector2 backward;
	static const Vector2 left;
	static const Vector2 right;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 one;
	static const Vector2 zero;
};

std::ostream& operator<<(std::ostream& os, const Vector2& vector3);
std::istream& operator>>(std::istream& is, Vector2& vector3);

#endif
