#pragma once
#include "shader.h"
#include "../math/mat4.h"
#include <GL/glew.h>

namespace VR {

	class OpenGLShader : public Shader {
		GLuint vertexShader, fragmentShader, shaderProgram;
	public:
		void init() override;
		void useShader() const;
		void setPerspectiveMatrix(const math::mat4& perspectiveMatrix) const;
		void setViewMatrix(const math::mat4& viewMatrix) const;

		~OpenGLShader() override;
	};

}