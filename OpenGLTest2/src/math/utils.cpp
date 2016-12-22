#include "utils.h"

namespace VR { namespace math {

float Utils::toRadians(float radians) {
	return (float)radians * PI / 180.0f;
}

} }