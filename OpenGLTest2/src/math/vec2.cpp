#include "vec2.h"
#include "mat4.h"
#include <math.h>

namespace VR {
	namespace math {

		vec2::vec2(const float& x, const float& y) : x{ x }, y{ y } { }

		float vec2::Magnitude() const {
			return (float)sqrt(x * x + y * y);
		}

		vec2 vec2::Normalize() const {
			float length = Magnitude();
			return vec2(x / length, y / length);
		}

		float& vec2::operator[](const int& index) {
			return *((float*)this + index);
		}

		float vec2::operator*(const vec2& rhs) const {
			return (x * rhs.x + y * rhs.y);
		}

		vec2 vec2::operator-(const vec2& rhs) const {
			vec2 result = *this;
			result.x -= rhs.x;
			result.y -= rhs.y;

			return result;
		}

	}
}