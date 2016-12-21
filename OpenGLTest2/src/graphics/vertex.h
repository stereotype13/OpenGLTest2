#pragma once
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"

namespace VR {

	struct Vertex {
		VR::math::vec3 Position;
		VR::math::vec4 Color;

		Vertex(VR::math::vec3& position, VR::math::vec4& color) : Position{ position }, Color{ color } {};
	};

}