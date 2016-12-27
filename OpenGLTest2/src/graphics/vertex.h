#pragma once
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"

namespace VR {

	struct Vertex {
		VR::math::vec3 Position;
		VR::math::vec4 Color;
		VR::math::vec2 TextureCoordinate;

		Vertex(const VR::math::vec3& position, const VR::math::vec4& color) : Position{ position }, Color{ color } {}
		Vertex(const VR::math::vec3& position, const VR::math::vec4& color, const VR::math::vec2& textureCoordinate) : Position{ position }, Color{ color }, TextureCoordinate{ textureCoordinate } {}
	};

}