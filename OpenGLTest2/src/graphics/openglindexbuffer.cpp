#include "openglindexbuffer.h"

namespace VR {

	void OpenGLIndexBuffer::init(unsigned int size) {
		mSize = size;

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO);

		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize * sizeof(GLfloat), 0, GL_STATIC_DRAW);

		
	}

	void OpenGLIndexBuffer::resize(unsigned int size) {
		mSize = size;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize * sizeof(GLfloat), 0, GL_STATIC_DRAW);
	}
	
	void OpenGLIndexBuffer::map() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO);
		mBuffer = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void OpenGLIndexBuffer::setData(const std::vector<GLuint>& data) {
		for (auto& index : data) {
			*mBuffer = index;
			++mBuffer;
		}
	}

	void OpenGLIndexBuffer::unmap() {
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &mVBO);
	}

}