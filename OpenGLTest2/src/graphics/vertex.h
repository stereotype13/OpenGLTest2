#pragma once
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"

namespace VR {

	struct Vertex {
		VR::math::vec3 Position;
		VR::math::vec4 Color;
		float TextureID;
		VR::math::vec2 TextureCoordinate;
		VR::math::vec3 SurfaceNormal;

		Vertex(const VR::math::vec3& position, const VR::math::vec4& color) : Position{ position }, Color{ color } {}
		Vertex(const VR::math::vec3& position, const VR::math::vec4& color, float textureID, const VR::math::vec2& textureCoordinate) : Position{ position }, Color{ color }, TextureID{ textureID }, TextureCoordinate{ textureCoordinate } {}
		Vertex(const VR::math::vec3& position, const VR::math::vec4& color, float textureID, const VR::math::vec2& textureCoordinate, const VR::math::vec3& surfaceNormal) : Position{ position }, Color{ color }, TextureID{ textureID }, TextureCoordinate { textureCoordinate }, SurfaceNormal{ surfaceNormal } {}
	};

}