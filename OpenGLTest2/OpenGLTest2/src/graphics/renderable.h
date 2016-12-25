#pragma once
#include "vertex.h"
#include <vector>

namespace VR {

	class Renderable {
	public:
		virtual std::vector<Vertex*>& getVertices() = 0;
		virtual std::vector<unsigned int>& getIndices() = 0;
		virtual unsigned int getVertexCount() = 0;
		virtual unsigned int getIndexCount() = 0;
		virtual ~Renderable() {};
	};

}
