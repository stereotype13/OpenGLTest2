#pragma once


namespace VR {
	
	class Buffer {
	protected:
		unsigned int mSize;
	public:
		virtual void init(unsigned int size) = 0;
	};

}