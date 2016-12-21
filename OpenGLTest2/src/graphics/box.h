#pragma once
#include <vector>
#include "renderable.h"

namespace VR {

	class Box : public Renderable {
		std::vector<Vertex*> mVertices;
		std::vector<unsigned int> mIndices;
	public:
		Box();

		std::vector<Vertex*>& getVertices() override;

		std::vector<unsigned int>& getIndices() override;

		unsigned int getVertexCount() override;

		unsigned int getIndexCount() override;

		~Box();
	};
}