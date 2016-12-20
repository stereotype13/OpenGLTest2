#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <chrono>
#include <cmath>
#include <vector>

#define PI 3.14159265358979323846
#define LOG(x) std::cout << x << std::endl;

typedef std::chrono::high_resolution_clock HighResolutionClock;
typedef std::chrono::duration<float, std::milli> milliseconds_type;

float toRadians(float radians) {
	return radians * PI / 180;
}

class vec3 {
	GLfloat mData[3];

public:
	vec3() = default;
	vec3(const GLfloat& x1, const GLfloat& x2, const GLfloat& x3) {
		mData[0] = x1;
		mData[1] = x2;
		mData[2] = x3;
	}

	float Magnitude() {
		return std::sqrt(mData[0] * mData[0] + mData[1] * mData[1] + mData[2] * mData[2]);
	}

	vec3 Normalize() {
		float length = Magnitude();
		return vec3(mData[0] / length, mData[1] / length, mData[2] / length);
	}

	vec3 vec3::Cross(const vec3& other) const
	{
		return vec3(mData[1] * other.mData[2] - mData[2] * other.mData[1], mData[2] * other.mData[0] - mData[0] * other.mData[2], mData[0] * other.mData[1] - mData[1] * other.mData[0]);
	}

	
	GLfloat& operator[](const int& index) {
		return mData[index];
	}

	GLfloat operator*(vec3& rhs) {
		return (mData[0] * rhs[0] + mData[1] * rhs[1] + mData[2] * rhs[2]);
	}

	vec3 operator-(vec3& rhs) {
		vec3 result = *this;
		result[0] -= rhs.mData[0];
		result[1] -= rhs.mData[1];
		result[2] -= rhs.mData[2];
		return result;
	}
};

class vec4 {
	GLfloat mData[4];

public:
	vec4() = default;
	vec4(const GLfloat x1, const GLfloat x2, const GLfloat x3, const GLfloat x4) {
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
	virtual unsigned int getVertexCount() = 0;
	virtual unsigned int getIndexCount() = 0;
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

	Rectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, vec4& color) {
		auto upperLeft = new Vertex(vec3(x, y, z), color);
		mVertices.push_back(upperLeft);

		auto lowerLeft = new Vertex(vec3(x, y - height, z), color);
		mVertices.push_back(lowerLeft);

		auto lowerRight = new Vertex(vec3(x + width, y - height, z), color);
		mVertices.push_back(lowerRight);

		auto upperRight = new Vertex(vec3(x + width, y, z), color);
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

	unsigned int getVertexCount() override {
		return mVertices.size();
	}

	unsigned int getIndexCount() override {
		return mIndices.size();
	}

	~Rectangle() {
		for (auto& vertex : mVertices) {
			delete vertex;
		}
	}
};

class Box : public Renderable {
	std::vector<Vertex*> mVertices;
	std::vector<GLuint> mIndices;
public:
	Box() {
		//front
		auto front1 = new Vertex(vec3(-0.5f, 0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
		mVertices.push_back(front1);

		auto front2 = new Vertex(vec3(-0.5f, -0.5f, 0.5f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
		mVertices.push_back(front2);

		auto front3 = new Vertex(vec3(0.5f, -0.5f, 0.5f), vec4(0.0f, 0.0f, 1.0f, 1.0f));
		mVertices.push_back(front3);

		auto front4 = new Vertex(vec3(0.5f, 0.5f, 0.5f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
		mVertices.push_back(front4);

		//back
		auto back1 = new Vertex(vec3(0.5f, 0.5f, -0.5f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
		mVertices.push_back(back1);

		auto back2 = new Vertex(vec3(0.5f, -0.5f, -0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
		mVertices.push_back(back2);

		auto back3 = new Vertex(vec3(-0.5f, -0.5f, -0.5f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
		mVertices.push_back(back3);

		auto back4 = new Vertex(vec3(-0.5f, 0.5f, -0.5f), vec4(0.0f, 0.0f, 1.0f, 1.0f));
		mVertices.push_back(back4);

		//indices
		mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(2);
		mIndices.push_back(2); mIndices.push_back(3); mIndices.push_back(0);
		
		mIndices.push_back(3); mIndices.push_back(2); mIndices.push_back(5);
		mIndices.push_back(5); mIndices.push_back(4); mIndices.push_back(3);

		mIndices.push_back(4); mIndices.push_back(5); mIndices.push_back(6);
		mIndices.push_back(6); mIndices.push_back(7); mIndices.push_back(4);

		mIndices.push_back(7); mIndices.push_back(6); mIndices.push_back(1);
		mIndices.push_back(1); mIndices.push_back(0); mIndices.push_back(7);

		mIndices.push_back(7); mIndices.push_back(0); mIndices.push_back(3);
		mIndices.push_back(3); mIndices.push_back(4); mIndices.push_back(7);

		mIndices.push_back(1); mIndices.push_back(6); mIndices.push_back(2);
		mIndices.push_back(6); mIndices.push_back(5); mIndices.push_back(2);
	}

	std::vector<Vertex*>& getVertices() override {
		return mVertices;
	}

	std::vector<GLuint>& getIndices() override {
		return	mIndices;
	}

	unsigned int getVertexCount() override {
		return mVertices.size();
	}

	unsigned int getIndexCount() override {
		return mIndices.size();
	}

	~Box() {
		for (auto& vertex : mVertices) {
			delete vertex;
		}
	}
};

class mat4 {
public:
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

	vec4 getColumn(const int& index) {
		vec4 result;
		result[0] = mData[0 * 4 + index];
		result[1] = mData[1 * 4 + index];
		result[2] = mData[2 * 4 + index];
		result[3] = mData[3 * 4 + index];
		return result;
	}

	mat4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4) {
		mRows[0] = row1;
		mRows[1] = row2;
		mRows[2] = row3;
		mRows[3] = row4;

	}

	vec4& operator[](const int index) {
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

	mat4& operator*(const mat4& other) {
		float data[16];
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += mData[e + row * 4] * other.mData[col + e * 4];
				}
				data[col + row * 4] = sum;
			}
		}
		memcpy(mData, data, 4 * 4 * sizeof(float));
		return *this;
	}

	
	static mat4 Identity();

	static mat4 Translation(vec3& translationVector);

	static mat4 RotationX(const GLfloat& theta);

	static mat4 RotationY(const GLfloat& theta);

	static mat4 RotationZ(const GLfloat& theta);

	static mat4 Transpose(mat4& matrix);

	static mat4 Perspective(float fov, float aspectRatio, float near, float far);

	static mat4 LookAt(vec3& camera, vec3& object, vec3& up);
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

mat4 mat4::RotationX(const GLfloat& theta) {
	mat4 rotationMatrix = Identity();
	GLfloat c = std::cos(theta);
	GLfloat s = std::sin(theta);
	rotationMatrix.mData[1 * 4 + 1] = c;
	rotationMatrix.mData[1 * 4 + 2] = -s;
	rotationMatrix.mData[2 * 4 + 1] = s;
	rotationMatrix.mData[2 * 4 + 2] = c;
	return rotationMatrix;
}

mat4 mat4::RotationY(const GLfloat& theta) {
	mat4 rotationMatrix = Identity();
	GLfloat c = std::cos(theta);
	GLfloat s = std::sin(theta);
	rotationMatrix.mData[0 * 4 + 0] = c;
	rotationMatrix.mData[0 * 4 + 2] = s;
	rotationMatrix.mData[2 * 4 + 0] = -s;
	rotationMatrix.mData[2 * 4 + 2] = c;
	return rotationMatrix;
}

mat4 mat4::RotationZ(const GLfloat& theta) {
	mat4 rotationMatrix = Identity();
	GLfloat c = std::cos(theta);
	GLfloat s = std::sin(theta);
	rotationMatrix.mData[0 * 4 + 0] = c;
	rotationMatrix.mData[0 * 4 + 1] = -s;
	rotationMatrix.mData[1 * 4 + 0] = s;
	rotationMatrix.mData[1 * 4 + 1] = c;
	return rotationMatrix;
}

mat4 mat4::Transpose(mat4& matrix)
{
	
	return mat4(
		matrix.getColumn(0),
		matrix.getColumn(1),
		matrix.getColumn(2),
		matrix.getColumn(3)
		);
		
}

mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result(1.0f);

	float q = 1.0f / std::tan(toRadians(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.mData[0 + 0 * 4] = a;
	result.mData[1 + 1 * 4] = q;
	result.mData[2 + 2 * 4] = b;
	result.mData[2 + 3 * 4] = -1.0f;
	result.mData[3 + 2 * 4] = c;

	return result;
}

mat4 mat4::LookAt(vec3& camera, vec3& object, vec3& up)
{

	mat4 result = Identity();
	vec3 f = (object - camera).Normalize();
	vec3 s = f.Cross(up.Normalize());
	vec3 u = s.Cross(f);

	result.mData[0 + 0 * 4] = s[0];
	result.mData[0 + 1 * 4] = s[1];
	result.mData[0 + 2 * 4] = s[2];

	result.mData[1 + 0 * 4] = u[0];
	result.mData[1 + 1 * 4] = u[1];
	result.mData[1 + 2 * 4] = u[2];

	result.mData[2 + 0 * 4] = -f[0];
	result.mData[2 + 1 * 4] = -f[1];
	result.mData[2 + 2 * 4] = -f[2];

	return result * Translation(vec3(-camera[0], -camera[1], -camera[2]));
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

	

	Rectangle rectangle(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Box box;

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

	//Allocate enough space on video card for x verticies, each with 3 position and 4 color (total 7) values.
	glBufferData(GL_ARRAY_BUFFER, box.getVertexCount() * 7 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);

	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)((GLfloat*)NULL + 3));

	//Not the best way, but good enough for now. Want to do it in the same loop.
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, box.getIndexCount() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
	
	std::chrono::time_point<HighResolutionClock> startTimePoint;
	startTimePoint = HighResolutionClock::now();
	float ellapsedTime = 0.0f;
	float totalEllapsedTime = 0.0f;

	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(window))
	{
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		

		ellapsedTime = std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - startTimePoint).count() / 1000.0f;
		startTimePoint = HighResolutionClock::now();
		totalEllapsedTime += ellapsedTime;
		if (totalEllapsedTime > 2 * PI)
			totalEllapsedTime -= 2 * PI;

		//set the projection matrix
		mat4 perspectiveMatrix = mat4::Perspective(90.0f, 4.0f/3.0f, 0.1f, 100.0f);
		GLuint uniformPerspectiveMatrix = glGetUniformLocation(shaderProgram, "perspectiveMatrix");

		if (uniformPerspectiveMatrix != -1) {
			glUniformMatrix4fv(uniformPerspectiveMatrix, 1, GL_TRUE, (const GLfloat*)&perspectiveMatrix);
		}

		//set the view matrix
		mat4 viewMatrix = mat4::LookAt(vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		//map buffers
		GLfloat* vertexBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		mat4 translationMatrix = mat4::Translation(vec3(0.5 * std::sin(2 * totalEllapsedTime), 0.0f, 0.0f));
		mat4 rotationMatrixX = mat4::RotationX(totalEllapsedTime);
		mat4 rotationMatrixY = mat4::RotationY(totalEllapsedTime);
		int vertexCount = 0;
		for (auto& vertex : box.getVertices()) {
			//vec3 position = rotationMatrixY * (translationMatrix * (rotationMatrixZ * vertex->Position));
			vec3 position = viewMatrix * (rotationMatrixY * (rotationMatrixX * vertex->Position));

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
		for (auto& index : box.getIndices()) {
			*indexBuffer = index;
			++indexBuffer;
		}
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		
		glDrawElements(GL_TRIANGLES, box.getIndexCount(), GL_UNSIGNED_INT, 0);
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