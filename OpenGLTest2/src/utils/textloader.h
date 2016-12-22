#pragma once
#include <string>

namespace VR { namespace utils {

	class TextLoader {
	public:
		static std::string loadText(const std::string& filePath);
	};


} }