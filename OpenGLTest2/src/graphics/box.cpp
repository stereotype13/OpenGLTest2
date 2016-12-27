#include "box.h"

namespace VR {

	Box::Box() {
		//front
		auto front1 = new Vertex(VR::math::vec3(-0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f));
		mVertices.push_back(front1);

		auto front2 = new Vertex(VR::math::vec3(-0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f));
		mVertices.push_back(front2);

		auto front3 = new Vertex(VR::math::vec3(0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(1.0f, 0.0f));
		mVertices.push_back(front3);

		auto front4 = new Vertex(VR::math::vec3(0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 1.0f));
		mVertices.push_back(front4);

		//back
		auto back1 = new Vertex(VR::math::vec3(0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f));
		mVertices.push_back(back1);

		auto back2 = new Vertex(VR::math::vec3(0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f));
		mVertices.push_back(back2);

		auto back3 = new Vertex(VR::math::vec3(-0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 0.0f));
		mVertices.push_back(back3);

		auto back4 = new Vertex(VR::math::vec3(-0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(1.0f, 1.0f));
		mVertices.push_back(back4);

		//indices
		mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(2);
		mIndices.push_back(2); mIndices.push_back(3); mIndices.push_back(0);

		mIndices.push_back(3); mIndices.push_back(2); mIndices.push_back(5);
		mIndices.push_back(5); mIndices.push_back(4); mIndices.push_back(3);

		mIndices.push_back(4); mIndices.push_back(5); mIndices.push_back(6);
		mIndices.push_back(6); mIndices.push_back(7); mIndices.push_back(4);

		mIndices.push_back(7); mIndices.push_back(6); mIndices.push_back(1);
		mIndices.push_back(1); mIndices.push_back(0); mIndices.push_back(7);

		mIndices.push_back(7); mIndices.push_back(0); mIndices.push_back(3);
		mIndices.push_back(3); mIndices.push_back(4); mIndices.push_back(7);

		mIndices.push_back(1); mIndices.push_back(6); mIndices.push_back(2);
		mIndices.push_back(6); mIndices.push_back(5); mIndices.push_back(2);
	}

	std::vector<Vertex*>& Box::getVertices() {
		return mVertices;
	}

	std::vector<unsigned int>& Box::getIndices() {
		return	mIndices;
	}

	unsigned int Box::getVertexCount() {
		return mVertices.size();
	}

	unsigned int Box::getIndexCount() {
		return mIndices.size();
	}

	Box::~Box() {
		for (auto& vertex : mVertices) {
			delete vertex;
		}
	}

}