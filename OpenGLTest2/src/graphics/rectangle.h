#pragma once
#include "renderable.h"

namespace VR {

	class Rectangle : public Renderable {
		std::vector<Vertex*> mVertices;
		std::vector<unsigned int> mIndices;
	public:

		Rectangle(float x, float y, float width, float height, VR::math::vec4& color);

		Rectangle(float x, float y, float z, float width, float height, VR::math::vec4& color);

		std::vector<Vertex*>& getVertices() override;

		std::vector<unsigned int>& getIndices() override;

		unsigned int getVertexCount() override;

		unsigned int getIndexCount() override;

		~Rectangle();
	};

}
