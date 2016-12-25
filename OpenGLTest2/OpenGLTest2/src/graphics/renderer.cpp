#include "renderer.h"

namespace VR {

	Renderer::~Renderer() {
		for (auto& renderable : mRenderables)
			delete renderable;

		//If there are any unused transformations, delete them.
		while (mTransformationStack.size() > 0) {
			delete mTransformationStack.top();
			mTransformationStack.pop();
		}
	}

}
