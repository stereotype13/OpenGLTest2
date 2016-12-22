#pragma once

namespace VR {

	class Shader {
	public:
		virtual void init() = 0;
		virtual ~Shader() {}
	};

}