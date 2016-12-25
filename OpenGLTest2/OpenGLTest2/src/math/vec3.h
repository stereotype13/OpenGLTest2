#pragma once

namespace VR { namespace math {

//forward declaration
class mat4;

class vec3 {
public:
	float x, y, z;
	vec3() = default;
	vec3(const float& x, const float& y, const float& z);

	float Magnitude() const;

	vec3 Normalize() const;

	vec3 Cross(const vec3& other) const;

	float& operator[](const int& index);

	float operator*(const vec3& rhs) const;

	void operator*=(mat4& transform);

	vec3 operator-(const vec3& rhs) const;
};

} }


