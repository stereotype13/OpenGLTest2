#pragma once

namespace VR { namespace math {

class vec3 {
public:
	float x, y, z;
	vec3() = default;
	vec3(const float& x, const float& y, const float& z);

	float Magnitude();

	vec3 Normalize();

	vec3 vec3::Cross(const vec3& other) const;

	float& operator[](const int& index);

	float operator*(vec3& rhs);

	vec3 operator-(vec3& rhs);
};

} }


