#include "Vector2.hpp"
#include "Quaternion.h"

// Constants
const Vector2 Vector2::left (-1, 0);
const Vector2 Vector2::right (1, 0);
const Vector2 Vector2::up (0, 1);
const Vector2 Vector2::down (0, -1);
const Vector2 Vector2::one (1, 1);
const Vector2 Vector2::zero (0, 0);

Vector2 Vector2::operator+(const Vector2& right) const {
	Vector2 temp (*this);
	temp += right;
	return temp;
}

Vector2 Vector2::operator-(const Vector2& right) const {
	Vector2 temp (*this);
	temp -= right;
	return temp;
}

Vector2 Vector2::operator*(const Vector2& right) const {
	Vector2 temp (*this);
	temp *= right;
	return temp;
}

Vector2 Vector2::operator/(const Vector2& right) const {
	Vector2 temp (*this);
	temp /= right;
	return temp;
}

Vector2& Vector2::operator+=(const Vector2& right) {
	for (int index = 0; index < 2; ++index)
		data [index] += right.data [index];
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& right) {
	for (int index = 0; index < 2; ++index)
		data [index] -= right.data [index];
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& right) {
	for (int index = 0; index < 2; ++index)
		data [index] *= right.data [index];
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& right) {
	for (int index = 0; index < 2; ++index)
		data [index] /= right.data [index];
	return *this;
}

void Vector2::normalize () {
	*this = normalized ();
}

Vector2 Vector2::normalized () const {
	float lenghtInverse = 1 / absolute ();
	return Vector2 (
		data [0] * lenghtInverse,
		data [1] * lenghtInverse);
}

float Vector2::absolute () const {
	return sqrt (absolute2 ());
}

float Vector2::absolute2 () const {
	float ret = 0;
	for (int index = 0; index < 2; ++index)
		ret += data [index] * data [index];
	return ret;
}

float Vector2::dotProduct (const Vector2& left, const Vector2& right) {
	float ret = 0;
	for (int index = 0; index < 2; ++index)
		ret += left.data [index] * right.data [index];
	return ret;
}

float Vector2::angleBetweenVectors (const Vector2& otherVector) const {
	// Two vectors form a triangle with sides abs(v1), abs(v1) and abs(v1-v2).
	// Apply good old geometry and you get this.
	return acos (
		dotProduct (*this, otherVector)
		/
		sqrt (absolute2 () * otherVector.absolute2 ())
	);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vector2) {
	os << '{' << vector2.data [0] << ',' << vector2.data [1] << '}';
	return os;
}

std::istream& operator>>(std::istream& is, Vector2& vector2) {
	is.ignore (256, '{');
	is >> vector2 [0];
	is.ignore (256, ',');
	is >> vector2 [1];
	is.ignore (256, '}');
	return is;
}
