#pragma once
#include "buffer.h"
#include "vertex.h"
#include <vector>
#include <GL/glew.h>

namespace VR {

	class OpenGLArrayBuffer : public Buffer {
		GLuint mVBO;
		GLfloat* mBuffer;
	public:
		void init(unsigned int size) override;
		void resize(unsigned int size) override;
		void map();
		void setData(const std::vector<Vertex>& data);
		void unmap();
		~OpenGLArrayBuffer();
	};

}