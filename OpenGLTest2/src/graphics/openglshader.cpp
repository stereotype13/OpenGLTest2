#include "openglshader.h"
#include "../utils/textloader.h"
#include <string>
#include <GL/glew.h>
#include <stdio.h>

namespace VR {

	void OpenGLShader::init() {
		char* version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		printf("Supported GLSL version is %s.\n", version);

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		std::string vertexShaderPath;
#ifdef _OS_X_
		vertexShaderPath = "/Users/stereotype13/Documents/OpenGLTest/OpenGLTest/OpenGLTest/shaders/vertexShader.vertex";
#else
		vertexShaderPath = "shaders\\vertexShader.vertex";
#endif
		std::string vertexShaderSource = VR::utils::TextLoader::loadText(vertexShaderPath);
		const char* vertexShaderSourcCString = vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderSourcCString, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {

			int maxLength;

			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			char* vertexInfoLog = (char*)malloc(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, vertexInfoLog);

			printf(vertexInfoLog);

			free(vertexInfoLog);

			//return false;

		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragmentShaderPath;
#ifdef _OS_X_
		fragmentShaderPath = "/Users/stereotype13/Documents/OpenGLTest/OpenGLTest/OpenGLTest/shaders/fragmentShader.fragment";
#else
		fragmentShaderPath = "shaders\\fragmentShader.fragment";
#endif
		std::string fragmentShaderSource = VR::utils::TextLoader::loadText(fragmentShaderPath);
		const char* fragmentShaderCString = fragmentShaderSource.c_str();
		glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderCString, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			int maxLength;

			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			char* fragmentInfoLog = (char*)malloc(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, fragmentInfoLog);

			printf(fragmentInfoLog);

			free(fragmentInfoLog);

			//return false;

		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);
	}

	void OpenGLShader::useShader() const {
		glUseProgram(shaderProgram);
	}

	void OpenGLShader::setPerspectiveMatrix(const math::mat4& perspectiveMatrix) const {
		GLuint perspectiveMatrixID = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
		if (perspectiveMatrixID != -1) {
			glUniformMatrix4fv(perspectiveMatrixID, 1, GL_TRUE, (const float*)&perspectiveMatrix);
		}
	}

	void OpenGLShader::setViewMatrix(const math::mat4& viewMatrix) const {
		GLuint viewMatrixID = glGetUniformLocation(shaderProgram, "viewMatrix");
		if (viewMatrixID != -1) {
			glUniformMatrix4fv(viewMatrixID, 1, GL_TRUE, (const float*)&viewMatrix);
		}
	}

	void OpenGLShader::setModelMatrix(const math::mat4& modelMatrix) const {
		GLuint modelMatrixID = glGetUniformLocation(shaderProgram, "modelMatrix");
		if (modelMatrixID != -1) {
			glUniformMatrix4fv(modelMatrixID, 1, GL_TRUE, (const float*)&modelMatrix);
		}
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteShader(shaderProgram);
	}

}