#pragma once

namespace VR {
	namespace math {


		class vec2 {
		public:
			float x, y;
			vec2() = default;
			vec2(const float& x, const float& y);

			float Magnitude() const;

			vec2 Normalize() const;

			float& operator[](const int& index);

			float operator*(const vec2& rhs) const;

			vec2 operator-(const vec2& rhs) const;
		};

	}
}




