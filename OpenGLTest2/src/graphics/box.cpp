#include "box.h"

namespace VR {

	Box::Box() {
		//front
		auto front1 = new Vertex(VR::math::vec3(-0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f), VR::math::vec3(0.0f, 0.0f, 1.0f));
		mVertices.push_back(front1);

		auto front2 = new Vertex(VR::math::vec3(-0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f), VR::math::vec3(0.0f, 0.0f, 1.0f));
		mVertices.push_back(front2);

		auto front3 = new Vertex(VR::math::vec3(0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(1.0f, 0.0f), VR::math::vec3(0.0f, 0.0f, 1.0f));
		mVertices.push_back(front3);

		auto front4 = new Vertex(VR::math::vec3(0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 1.0f), VR::math::vec3(0.0f, 0.0f, 1.0f));
		mVertices.push_back(front4);

		//right
		auto right1 = new Vertex(VR::math::vec3(0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f), VR::math::vec3(1.0f, 0.0f, 0.0f));
		mVertices.push_back(right1);

		auto right2 = new Vertex(VR::math::vec3(0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(0.0f, 0.0f), VR::math::vec3(1.0f, 0.0f, 0.0f));
		mVertices.push_back(right2);

		auto right3 = new Vertex(VR::math::vec3(0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 0.0f), VR::math::vec3(1.0f, 0.0f, 0.0f));
		mVertices.push_back(right3);

		auto right4 = new Vertex(VR::math::vec3(0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 1.0f), VR::math::vec3(1.0f, 0.0f, 0.0f));
		mVertices.push_back(right4);

		//back
		auto back1 = new Vertex(VR::math::vec3(0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f), VR::math::vec3(0.0f, 0.0f, -1.0f));
		mVertices.push_back(back1);

		auto back2 = new Vertex(VR::math::vec3(0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f), VR::math::vec3(0.0f, 0.0f, -1.0f));
		mVertices.push_back(back2);

		auto back3 = new Vertex(VR::math::vec3(-0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 0.0f), VR::math::vec3(0.0f, 0.0f, -1.0f));
		mVertices.push_back(back3);

		auto back4 = new Vertex(VR::math::vec3(-0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(1.0f, 1.0f), VR::math::vec3(0.0f, 0.0f, -1.0f));
		mVertices.push_back(back4);

		//left
		auto left1 = new Vertex(VR::math::vec3(-0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(0.0f, 1.0f), VR::math::vec3(-1.0f, 0.0f, 0.0f));
		mVertices.push_back(left1);

		auto left2 = new Vertex(VR::math::vec3(-0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f), VR::math::vec3(-1.0f, 0.0f, 0.0f));
		mVertices.push_back(left2);

		auto left3 = new Vertex(VR::math::vec3(-0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 0.0f), VR::math::vec3(-1.0f, 0.0f, 0.0f));
		mVertices.push_back(left3);

		auto left4 = new Vertex(VR::math::vec3(-0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 1.0f), VR::math::vec3(-1.0f, 0.0f, 0.0f));
		mVertices.push_back(left4);

		//top
		auto top1 = new Vertex(VR::math::vec3(-0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f), VR::math::vec3(0.0f, 1.0f, 0.0f));
		mVertices.push_back(top1);

		auto top2 = new Vertex(VR::math::vec3(0.5f, 0.5f, 0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f), VR::math::vec3(0.0f, 1.0f, 0.0f));
		mVertices.push_back(top2);

		auto top3 = new Vertex(VR::math::vec3(0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 0.0f), VR::math::vec3(0.0f, 1.0f, 0.0f));
		mVertices.push_back(top3);

		auto top4 = new Vertex(VR::math::vec3(-0.5f, 0.5f, -0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(1.0f, 1.0f), VR::math::vec3(0.0f, 1.0f, 0.0f));
		mVertices.push_back(top4);

		//bottom
		auto bottom1 = new Vertex(VR::math::vec3(-0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 1.0f), VR::math::vec3(0.0f, -1.0f, 0.0f));
		mVertices.push_back(bottom1);

		auto bottom2 = new Vertex(VR::math::vec3(0.5f, -0.5f, -0.5f), VR::math::vec4(1.0f, 0.0f, 0.0f, 1.0f), VR::math::vec2(0.0f, 0.0f), VR::math::vec3(0.0f, -1.0f, 0.0f));
		mVertices.push_back(bottom2);

		auto bottom3 = new Vertex(VR::math::vec3(0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 0.0f, 1.0f, 1.0f), VR::math::vec2(1.0f, 0.0f), VR::math::vec3(0.0f, -1.0f, 0.0f));
		mVertices.push_back(bottom3);

		auto bottom4 = new Vertex(VR::math::vec3(-0.5f, -0.5f, 0.5f), VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f), VR::math::vec2(1.0f, 1.0f), VR::math::vec3(0.0f, -1.0f, 0.0f));
		mVertices.push_back(bottom4);
				

		//indices
		for (int i = 0; i < 4 * 6; i += 4) {
			mIndices.push_back(0 + i); mIndices.push_back(1 + i); mIndices.push_back(2 + i);
			mIndices.push_back(2 + i); mIndices.push_back(3 + i); mIndices.push_back(0 + i);
		}
		
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