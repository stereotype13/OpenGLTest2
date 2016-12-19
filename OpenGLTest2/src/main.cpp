#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <chrono>
#include <cmath>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

typedef std::chrono::high_resolution_clock HighResolutionClock;
typedef std::chrono::duration<float, std::milli> milliseconds_type;

class vec3 {
	GLfloat mData[3];

public:
	vec3() = default;
	vec3(const GLfloat& x1, const GLfloat& x2, const GLfloat& x3) {
		mData[0] = x1;
		mData[1] = x2;
		mData[2] = x3;
	}

	GLfloat& operator[](const int& index) {
		return mData[index];
	}

	GLfloat operator*(vec3& rhs) {
		return (mData[0] * rhs[0] + mData[1] * rhs[1] + mData[2] * rhs[2]);
	}
};

class vec4 {
	GLfloat mData[4];

public:
	vec4() = default;
	vec4(const GLfloat& x1, const GLfloat& x2, const GLfloat& x3, const GLfloat& x4) {
		mData[0] = x1;
		mData[1] = x2;
		mData[2] = x3;
		mData[3] = x4;
	}

	GLfloat& operator[](const int& index) {
		return mData[index];
	}

	GLfloat operator*(vec4& rhs) {
		return (mData[0] * rhs[0] + mData[1] * rhs[1] + mData[2] * rhs[2] + mData[3] * rhs[3]);
	}
};

struct Vertex {
	vec3 Position;
	vec4 Color;

	Vertex(vec3& position, vec4& color) : Position{ position }, Color{ color } {};
};

class Renderable {
public:
	virtual std::vector<Vertex*>& getVertices() = 0;
	virtual std::vector<unsigned int>& getIndices() = 0;
	virtual ~Renderable() {};
};

class Rectangle : public Renderable {
	std::vector<Vertex*> mVertices;
	std::vector<GLuint> mIndices;
public:

	Rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, vec4& color) {
		auto upperLeft = new Vertex(vec3(x, y, 0.0f), color);
		mVertices.push_back(upperLeft);

		auto lowerLeft = new Vertex(vec3(x, y - height, 0.0f), color);
		mVertices.push_back(lowerLeft);

		auto lowerRight = new Vertex(vec3(x + width, y - height, 0.0f), color);
		mVertices.push_back(lowerRight);

		auto upperRight = new Vertex(vec3(x + width, y, 0.0f), color);
		mVertices.push_back(upperRight);

		mIndices.push_back(0);
		mIndices.push_back(1);
		mIndices.push_back(2);
		mIndices.push_back(2);
		mIndices.push_back(3);
		mIndices.push_back(0);
	}

	std::vector<Vertex*>& getVertices() override {
		return mVertices;
	}

	std::vector<GLuint>& getIndices() override {
		return	mIndices;
	}

	~Rectangle() {
		for (auto& vertex : mVertices) {
			delete vertex;
		}
	}
};

class mat4 {
	union {
		GLfloat mData[4 * 4];
		vec4 mRows[4];
	};

public:
	mat4(const GLfloat& diagonal) {
		memset(mData, 0.0f, 16 * sizeof(GLfloat));
	
		mData[0 + 0 * 4] = diagonal;
		mData[1 + 1 * 4] = diagonal;
		mData[2 + 2 * 4] = diagonal;
		mData[3 + 3 * 4] = diagonal;
	}

	vec4& operator[](const int& index) {
		return mRows[index];
	}

	vec4 operator*(vec4& rhs) {
		vec4 result;
		result[0] = mData[0 * 4 + 0] * rhs[0] + mData[0 * 4 + 1] * rhs[1] + mData[0 * 4 + 2] * rhs[2] + mData[0 * 4 + 3] * rhs[3];
		result[1] = mData[1 * 4 + 0] * rhs[0] + mData[1 * 4 + 1] * rhs[1] + mData[1 * 4 + 2] * rhs[2] + mData[1 * 4 + 3] * rhs[3];
		result[2] = mData[2 * 4 + 0] * rhs[0] + mData[2 * 4 + 1] * rhs[1] + mData[2 * 4 + 2] * rhs[2] + mData[2 * 4 + 3] * rhs[3];
		result[3] = mData[3 * 4 + 0] * rhs[0] + mData[3 * 4 + 1] * rhs[1] + mData[3 * 4 + 2] * rhs[2] + mData[3 * 4 + 3] * rhs[3];
		return result;
	}

	vec3 operator*(vec3& rhs) {
		vec3 result;
		result[0] = mData[0 * 4 + 0] * rhs[0] + mData[0 * 4 + 1] * rhs[1] + mData[0 * 4 + 2] * rhs[2] + mData[0 * 4 + 3];
		result[1] = mData[1 * 4 + 0] * rhs[0] + mData[1 * 4 + 1] * rhs[1] + mData[1 * 4 + 2] * rhs[2] + mData[1 * 4 + 3];
		result[2] = mData[2 * 4 + 0] * rhs[0] + mData[2 * 4 + 1] * rhs[1] + mData[2 * 4 + 2] * rhs[2] + mData[2 * 4 + 3];
		return result;
	}

	static mat4 Identity();

	static mat4 Translation(vec3& translationVector);
};

mat4 mat4::Identity() {
	return mat4(1.0f);
}

mat4 mat4::Translation(vec3& translationVector) {
	mat4 translationMatrix = Identity();
	translationMatrix.mData[0 * 4 + 3] = translationVector[0];
	translationMatrix.mData[1 * 4 + 3] = translationVector[1];
	translationMatrix.mData[2 * 4 + 3] = translationVector[2];
	return translationMatrix;
}

std::string loadSource(const std::string& path) {
	FILE* file;

	size_t fileLength, readLength;
	file = fopen(path.c_str(), "r");
	if (!file) {
		LOG("Error: Shader source file not found.");
		return 0;
	}
	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);
	std::string buffer(fileLength, 0);

	readLength = fread(&buffer[0], 1, fileLength, file);
	buffer[fileLength] = '\0';
	fclose(file);

	return buffer;
}

int main() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */

	

	Rectangle rectangle(-0.5f, 0.5f, 1.0f, 1.0f, vec4(0.0f, 1.0f, 0.0f, 1.0f));

	GLuint VAO;
	GLuint VBO[2];

	glewInit();
	

	//begin compiling shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderSource = loadSource("shaders\\vertexShader.vertex");
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

		LOG(vertexInfoLog);

		free(vertexInfoLog);

		return false;

	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderSource = loadSource("shaders\\fragmentShader.fragment");
	const char* fragmentShaderCString = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderCString, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		int maxLength;

		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		char* fragmentInfoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, fragmentInfoLog);

		LOG(fragmentInfoLog);

		free(fragmentInfoLog);

		return false;

	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//glBindAttribLocation(shaderProgram, 0, "position");
	//glBindAttribLocation(shaderProgram, 1, "color");

	glLinkProgram(shaderProgram);
	//end compiling shaders

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	//Allocate enough space on video card for 4 verticies, each with 3 position and 4 color (total 7) values.
	glBufferData(GL_ARRAY_BUFFER, 4 * 7 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);

	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)((GLfloat*)NULL + 3));

	//Not the best way, but good enough for now. Want to do it in the same loop.
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), NULL, GL_STATIC_DRAW);
	
	std::chrono::time_point<HighResolutionClock> startTimePoint;
	startTimePoint = HighResolutionClock::now();
	float ellapsedTime = 0.0f;
	float totalEllapsedTime = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		

		ellapsedTime = std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - startTimePoint).count() / 1000.0f;
		startTimePoint = HighResolutionClock::now();
		totalEllapsedTime += ellapsedTime;
		if (totalEllapsedTime > 2 * 3.14159265358979323846)
			totalEllapsedTime -= 2 * 3.14159265358979323846;

		GLfloat* vertexBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		mat4 translationMatrix = mat4::Translation(vec3(0.5 * std::sin(2 * totalEllapsedTime), 0.0f, 0.0f));
		int vertexCount = 0;
		for (auto& vertex : rectangle.getVertices()) {
			vec3 position = translationMatrix * vertex->Position;

			vertexBuffer[0 + vertexCount] = position[0];
			vertexBuffer[1 + vertexCount] = position[1];
			vertexBuffer[2 + vertexCount] = position[2];
			vertexBuffer[3 + vertexCount] = vertex->Color[0];
			vertexBuffer[4 + vertexCount] = vertex->Color[1];
			vertexBuffer[5 + vertexCount] = vertex->Color[2];
			vertexBuffer[6 + vertexCount] = vertex->Color[3];
			vertexBuffer += 7;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		GLuint* indexBuffer = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (auto& index : rectangle.getIndices()) {
			*indexBuffer = index;
			++indexBuffer;
		}
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteShader(shaderProgram);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}