#pragma once
#include "renderable.h"
#include "../math/mat4.h"
#include <vector>
#include <stack>

namespace VR {

	class Renderer {
	protected:
		std::vector<Renderable*> mRenderables;
		std::stack<math::mat4*> mTransformationStack;
	public:
		virtual void addRenderable(Renderable* renderable) = 0;
		virtual void addTransformation(math::mat4* transformation) = 0;
		virtual void render() = 0;
		virtual ~Renderer();
	};
}