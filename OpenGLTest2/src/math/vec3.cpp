#include "vec3.h"
#include <math.h>

namespace VR { namespace math {
	
vec3::vec3(const float& x, const float& y, const float& z) : x{ x }, y{ y }, z{ z } { }

float vec3::Magnitude() const {
	return (float)sqrt(x * x + y * y + z * z);
}

vec3 vec3::Normalize() const {
	float length = Magnitude();
	return vec3(x / length, y / length, z / length);
}

vec3 vec3::Cross(const vec3& other) const {
	return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float& vec3::operator[](const int& index) {
	return *((float*)this + index);
}

float vec3::operator*(const vec3& rhs) const {
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

vec3 vec3::operator-(const vec3& rhs) const {
	vec3 result = *this;
	result.x -= rhs.x;
	result.y -= rhs.y;
	result.z -= rhs.z;
	return result;
}

} }