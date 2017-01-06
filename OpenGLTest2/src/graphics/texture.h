#pragma once

namespace VR {

	class Texture {
	protected:
		const char* mFileName = nullptr;
		unsigned int mTextureID;
		unsigned int mWidth, mHeight;

		//pointer to image data
		unsigned char* mData = nullptr;

	public:
		virtual bool load() = 0;
		virtual bool unload() = 0;
		unsigned int getTextureID() { return mTextureID; }
	};

}