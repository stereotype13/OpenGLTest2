#include "openglrenderer.h"
#include "../math/constants.h"

namespace VR {

	OpenGLRenderer::OpenGLRenderer() {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		mShader.init();

		//temporary. since we're doing a cube, it will have 6 * 4 vertices
		mArrayBuffer.init(24);
		mIndexBuffer.init(36);

		mPerspectiveMatrix = VR::math::mat4::Perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		mViewMatrix = VR::math::mat4::LookAt(VR::math::vec3(0.0f, 0.0f, 1.0f), VR::math::vec3(0.0f, 0.0f, 0.0f), VR::math::vec3(0.0f, 1.0f, 0.0f));

		//temp texture stuff
		// Black/white checkerboard
		glActiveTexture(GL_TEXTURE0);
		
		glGenTextures(1, &mTextureID);
		float pixels[] = {
			0.5f, 0.5f, 0.5f,   1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.5f
		};
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		glActiveTexture(GL_TEXTURE1);

		glGenTextures(1, &mTextureID);
		float pixels2[] = {
			0.5f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f
		};
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	void OpenGLRenderer::addRenderable(Renderable* renderable) {
		mRenderables.push_back(renderable);
	
		for (Vertex* vertex : renderable->getVertices()) {
			mVertices.push_back(*vertex);
		}

		for (GLuint index : renderable->getIndices()) {
			mIndices.push_back(index + mIndexOffset);
		}

		mIndexOffset += renderable->getVertexCount() - 1;
	}

	void OpenGLRenderer::addTransformation(math::mat4* transformation) {
		mTransformationStack.push(transformation);
	}

	void OpenGLRenderer::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	}

	void OpenGLRenderer::refreshVertices() {
		mVertices.clear();
		for (const auto& renderable : mRenderables) {
			for (const Vertex* vertex : renderable->getVertices()) {
				mVertices.push_back(*vertex);
			}
		}
	}

	void OpenGLRenderer::onTick(const double& delta) {
		//do matrix transformations here
		//A lot of this stuff (i.e. creating transformation matrices) will eventually go into an 'Application' class, which would call the render() function.
		refreshVertices();

		mShader.useShader();

		const GLfloat omega = 0.5f;

		mTheta += delta * omega;
		if (mTheta > 2 * PI)
			mTheta -= 2 * PI;

		VR::math::mat4* rotationMatrixY = new VR::math::mat4();
		*rotationMatrixY = VR::math::mat4::RotationY(mTheta);

		VR::math::mat4* rotationMatrixX = new VR::math::mat4();
		*rotationMatrixX = VR::math::mat4::RotationX(mTheta);
		
		//addTransformation(rotationMatrixX);
		//addTransformation(rotationMatrixY);

		while (mTransformationStack.size() > 0) {
			for (Vertex& vertex : mVertices) {
				vertex.Position = *(mTransformationStack.top()) * vertex.Position;
			}
			delete mTransformationStack.top();
			mTransformationStack.pop();
		}

		mShader.setPerspectiveMatrix(mPerspectiveMatrix);
		mShader.setViewMatrix(mViewMatrix);

	
		mShader.setModelMatrix(*rotationMatrixX * *rotationMatrixY);

		
		GLint tempTexture = glGetUniformLocation(mShader.getShaderProgram(), "textures");
		
		const GLint asdf[2]{0, 1};
		glUniform1iv(tempTexture, 2, asdf);

		//end texture stuff

		mArrayBuffer.map();
		mArrayBuffer.setData(mVertices);
		mArrayBuffer.unmap();

		mIndexBuffer.map();
		mIndexBuffer.setData(mIndices);
		mIndexBuffer.unmap();

		render();

		//temporary. delete this later!!!!
		delete rotationMatrixX;
		delete rotationMatrixY;
	}

	void OpenGLRenderer::setPerspectiveMatrix(const math::mat4& perspectiveMatrix) {
		mPerspectiveMatrix = perspectiveMatrix;
	}

	OpenGLRenderer::~OpenGLRenderer() {
		glDeleteTextures(1, &mTextureID);
	}

}