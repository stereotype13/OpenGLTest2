#pragma once
#include "buffer.h"
#include <vector>
#include <GL/glew.h>

namespace VR {

	class OpenGLIndexBuffer : public Buffer {
		GLuint mVBO;
		GLuint* mBuffer = nullptr;
	public:
		void init(unsigned int size) override;
		void map();
		void setData(const std::vector<GLuint>& data);
		void unmap();
		~OpenGLIndexBuffer();
	};

}