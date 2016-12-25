#include "mat4.h"
#include "utils.h"
#include <math.h>
#include <string>

namespace VR { namespace math {

mat4::mat4(const float& diagonal) {
	memset(mData, 0.0f, 16 * sizeof(float));

	mData[0 + 0 * 4] = diagonal;
	mData[1 + 1 * 4] = diagonal;
	mData[2 + 2 * 4] = diagonal;
	mData[3 + 3 * 4] = diagonal;
}

vec4 mat4::getColumn(const int& index) {
	vec4 result;
	result.x = mData[0 * 4 + index];
	result.y = mData[1 * 4 + index];
	result.z = mData[2 * 4 + index];
	result.w = mData[3 * 4 + index];
	return result;
}

mat4::mat4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4) {
	mRows[0] = row1;
	mRows[1] = row2;
	mRows[2] = row3;
	mRows[3] = row4;
}

vec4& mat4::operator[](const int index) {
	return mRows[index];
}

const float& mat4::getElement(unsigned int index) {
	return mData[index];
}

vec4 mat4::operator*(const vec4& rhs) {
	vec4 result;
	result.x = mData[0 * 4 + 0] * rhs.x + mData[0 * 4 + 1] * rhs.y + mData[0 * 4 + 2] * rhs.z + mData[0 * 4 + 3] * rhs.w;
	result.y = mData[1 * 4 + 0] * rhs.x + mData[1 * 4 + 1] * rhs.y + mData[1 * 4 + 2] * rhs.z + mData[1 * 4 + 3] * rhs.w;
	result.z = mData[2 * 4 + 0] * rhs.x + mData[2 * 4 + 1] * rhs.y + mData[2 * 4 + 2] * rhs.z + mData[2 * 4 + 3] * rhs.w;
	result.w = mData[3 * 4 + 0] * rhs.x + mData[3 * 4 + 1] * rhs.y + mData[3 * 4 + 2] * rhs.z + mData[3 * 4 + 3] * rhs.w;
	return result;
}

vec3 mat4::operator*(const vec3& rhs) {
	vec3 result;
	result.x = mData[0 * 4 + 0] * rhs.x + mData[0 * 4 + 1] * rhs.y + mData[0 * 4 + 2] * rhs.z + mData[0 * 4 + 3];
	result.y = mData[1 * 4 + 0] * rhs.x + mData[1 * 4 + 1] * rhs.y + mData[1 * 4 + 2] * rhs.z + mData[1 * 4 + 3];
	result.z = mData[2 * 4 + 0] * rhs.x + mData[2 * 4 + 1] * rhs.y + mData[2 * 4 + 2] * rhs.z + mData[2 * 4 + 3];
	return result;
}

mat4& mat4::operator*(const mat4& other) {
	float data[16];
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0.0f;
			for (int e = 0; e < 4; ++e)	{
				sum += mData[e + row * 4] * other.mData[col + e * 4];
			}
			data[col + row * 4] = sum;
		}
	}
	memcpy(mData, data, 4 * 4 * sizeof(float));
	return *this;
}

mat4 mat4::Identity() {
	return mat4(1.0f);
}

mat4 mat4::Translation(const vec3& translationVector) {
	mat4 translationMatrix = Identity();
	translationMatrix.mData[0 * 4 + 3] = translationVector.x;
	translationMatrix.mData[1 * 4 + 3] = translationVector.y;
	translationMatrix.mData[2 * 4 + 3] = translationVector.z;
	return translationMatrix;
}

mat4 mat4::RotationX(const float& theta) {
	mat4 rotationMatrix = Identity();
	float c = cos(theta);
	float s = sin(theta);
	rotationMatrix.mData[1 * 4 + 1] = c;
	rotationMatrix.mData[1 * 4 + 2] = -s;
	rotationMatrix.mData[2 * 4 + 1] = s;
	rotationMatrix.mData[2 * 4 + 2] = c;
	return rotationMatrix;
}

mat4 mat4::RotationY(const float& theta) {
	mat4 rotationMatrix = Identity();
	float c = cos(theta);
	float s = sin(theta);
	rotationMatrix.mData[0 * 4 + 0] = c;
	rotationMatrix.mData[0 * 4 + 2] = s;
	rotationMatrix.mData[2 * 4 + 0] = -s;
	rotationMatrix.mData[2 * 4 + 2] = c;
	return rotationMatrix;
}

mat4 mat4::RotationZ(const float& theta) {
	mat4 rotationMatrix = Identity();
	float c = cos(theta);
	float s = sin(theta);
	rotationMatrix.mData[0 * 4 + 0] = c;
	rotationMatrix.mData[0 * 4 + 1] = -s;
	rotationMatrix.mData[1 * 4 + 0] = s;
	rotationMatrix.mData[1 * 4 + 1] = c;
	return rotationMatrix;
}

mat4 mat4::Transpose(mat4& matrix)
{

	return mat4(
		matrix.getColumn(0),
		matrix.getColumn(1),
		matrix.getColumn(2),
		matrix.getColumn(3)
		);
}

mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result(1.0f);

	float q = 1.0f / tan(Utils::toRadians(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.mData[0 + 0 * 4] = a;
	result.mData[1 + 1 * 4] = q;
	result.mData[2 + 2 * 4] = b;
	result.mData[2 + 3 * 4] = -1.0f;
	result.mData[3 + 2 * 4] = c;

	return result;
}

mat4 mat4::LookAt(const vec3& camera, const vec3& object, const vec3& up)
{

	mat4 result = Identity();
	vec3 f = (object - camera).Normalize();
	vec3 s = f.Cross(up.Normalize());
	vec3 u = s.Cross(f);

	result.mData[0 + 0 * 4] = s.x;
	result.mData[0 + 1 * 4] = s.y;
	result.mData[0 + 2 * 4] = s.z;

	result.mData[1 + 0 * 4] = u.x;
	result.mData[1 + 1 * 4] = u.y;
	result.mData[1 + 2 * 4] = u.z;

	result.mData[2 + 0 * 4] = -f.x;
	result.mData[2 + 1 * 4] = -f.y;
	result.mData[2 + 2 * 4] = -f.z;

	return result * Translation(vec3(-camera.x, -camera.y, -camera.z));
}

} }