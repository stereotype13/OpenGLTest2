#include "vec4.h"

namespace VR { namespace math {

vec4::vec4(const float x, const float y, const float z, const float w) : x{ x }, y{ y }, z{ z }, w{ w } { }

float& vec4::operator[](const int& index) {
	return *((float*)this + index);
}

float vec4::operator*(vec4& rhs) {
	return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}


} }