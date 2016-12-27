#pragma once
#include "renderer.h"
#include "vertex.h"
#include "openglarraybuffer.h"
#include "openglindexbuffer.h"
#include "../utils/clock.h"
#include <GL/glew.h>
#include "openglshader.h"
#include "../math/mat4.h"

namespace VR {

	class OpenGLRenderer : public Renderer, public utils::Clock::ClockListener {
		std::vector<Vertex> mVertices;
		std::vector<GLuint> mIndices;
			
		GLuint mIndexOffset = 0;

		GLuint mVAO;
		OpenGLArrayBuffer mArrayBuffer;
		OpenGLIndexBuffer mIndexBuffer;

		VR::OpenGLShader mShader;
		VR::math::mat4 mPerspectiveMatrix, mViewMatrix;

		GLfloat mTheta = 0.0f;

		void refreshVertices();

	public:
		OpenGLRenderer();
		void addRenderable(Renderable* renderable) override;
		void addTransformation(math::mat4* transformation) override;
		void render() override;

		void onTick(double delta) override;

		//temporary. We should have an Application class or Window class being responsible for this matrix.
		void setPerspectiveMatrix(const math::mat4& perspectiveMatrix);
	};

}
