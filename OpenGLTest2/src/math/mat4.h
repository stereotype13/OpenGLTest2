#pragma once
#include "vec3.h"
#include "vec4.h"

namespace VR { namespace math {

class mat4 {
public:
	union {
		float mData[4 * 4];
		vec4 mRows[4];
	};

	mat4(const float& diagonal);

	vec4 getColumn(const int& index);

	mat4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4);

	vec4& operator[](const int index);

	vec4 operator*(const vec4& rhs);

	vec3 operator*(const vec3& rhs);

	mat4& operator*(const mat4& other);

	static mat4 Identity();

	static mat4 Translation(const vec3& translationVector);

	static mat4 RotationX(const float& theta);

	static mat4 RotationY(const float& theta);

	static mat4 RotationZ(const float& theta);

	static mat4 Transpose(mat4& matrix);

	static mat4 Perspective(float fov, float aspectRatio, float near, float far);

	static mat4 LookAt(const vec3& camera, const vec3& object, const vec3& up);
};

} }
