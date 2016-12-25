#include "textloader.h"
#include <iostream>

namespace VR { namespace utils {

	std::string TextLoader::loadText(const std::string& filePath) {
		FILE* file;

		size_t fileLength, readLength;
		file = fopen(filePath.c_str(), "r");
		if (!file) {
			std::cout << "Error: Shader source file not found." << std::endl;;
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

} }