#pragma once

namespace VR { namespace math {

class vec4 {
public:
	float x, y, z, w;
	vec4() = default;
	vec4(const float x, const float y, const float z, const float w);

	float& operator[](const int& index);

	float operator*(vec4& rhs);
};


} }
