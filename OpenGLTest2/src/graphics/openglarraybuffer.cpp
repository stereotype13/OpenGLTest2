#include "openglarraybuffer.h"

namespace VR {

	void OpenGLArrayBuffer::init(unsigned int size) {
		mSize = size;

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		//Allocate enough space on video card for mSize verticies, each with 3 position and 4 color (total 7) values.
		glBufferData(GL_ARRAY_BUFFER, mSize * 7 * sizeof(GLfloat), 0, GL_STATIC_DRAW);

		//position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);

		//color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)((GLfloat*)0 + 3));
	}

	void OpenGLArrayBuffer::map() {
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		mBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void OpenGLArrayBuffer::setData(const std::vector<Vertex>& data) {
		int vertexCount = 0;
		for (const auto& vertex : data) {
			mBuffer[0 + vertexCount] = vertex.Position.x;
			mBuffer[1 + vertexCount] = vertex.Position.y;
			mBuffer[2 + vertexCount] = vertex.Position.z;
			mBuffer[3 + vertexCount] = vertex.Color.x;
			mBuffer[4 + vertexCount] = vertex.Color.y;
			mBuffer[5 + vertexCount] = vertex.Color.z;
			mBuffer[6 + vertexCount] = vertex.Color.w;
			mBuffer += 7;
		}
	}

	void OpenGLArrayBuffer::unmap() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	OpenGLArrayBuffer::~OpenGLArrayBuffer() {
		glDeleteBuffers(1, &mVBO);
	}

}