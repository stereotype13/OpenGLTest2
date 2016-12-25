#include "rectangle.h"

namespace VR {

	Rectangle::Rectangle(float x, float y, float width, float height, VR::math::vec4& color) {
		auto upperLeft = new Vertex(VR::math::vec3(x, y, 0.0f), color);
		mVertices.push_back(upperLeft);

		auto lowerLeft = new Vertex(VR::math::vec3(x, y - height, 0.0f), color);
		mVertices.push_back(lowerLeft);

		auto lowerRight = new Vertex(VR::math::vec3(x + width, y - height, 0.0f), color);
		mVertices.push_back(lowerRight);

		auto upperRight = new Vertex(VR::math::vec3(x + width, y, 0.0f), color);
		mVertices.push_back(upperRight);

		mIndices.push_back(0);
		mIndices.push_back(1);
		mIndices.push_back(2);
		mIndices.push_back(2);
		mIndices.push_back(3);
		mIndices.push_back(0);
	}

	Rectangle::Rectangle(float x, float y, float z, float width, float height, VR::math::vec4& color) {
		auto upperLeft = new Vertex(VR::math::vec3(x, y, z), color);
		mVertices.push_back(upperLeft);

		auto lowerLeft = new Vertex(VR::math::vec3(x, y - height, z), color);
		mVertices.push_back(lowerLeft);

		auto lowerRight = new Vertex(VR::math::vec3(x + width, y - height, z), color);
		mVertices.push_back(lowerRight);

		auto upperRight = new Vertex(VR::math::vec3(x + width, y, z), color);
		mVertices.push_back(upperRight);

		mIndices.push_back(0);
		mIndices.push_back(1);
		mIndices.push_back(2);
		mIndices.push_back(2);
		mIndices.push_back(3);
		mIndices.push_back(0);
	}

	std::vector<Vertex*>& Rectangle::getVertices() {
		return mVertices;
	}

	std::vector<unsigned int>& Rectangle::getIndices() {
		return	mIndices;
	}

	unsigned int Rectangle::getVertexCount() {
		return mVertices.size();
	}

	unsigned int Rectangle::getIndexCount() {
		return mIndices.size();
	}

	Rectangle::~Rectangle() {
		for (auto& vertex : mVertices) {
			delete vertex;
		}
	}

}