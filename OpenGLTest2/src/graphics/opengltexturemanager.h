#pragma once
#include "opengltexture.h"
#include <map>
#include <vector>

#define MAX_TEXTURE_SLOTS 32

namespace VR {
	

	class OpenGLTextureManager {
	private:
		static unsigned int mTextureIDCount;
		std::vector<OpenGLTexture*> mTextures;
		std::map<unsigned int, GLuint> mTextureSlots;
		int mOccupiedSlots = 0;

	public:
		static unsigned int getNewTextureID();
		void add(OpenGLTexture* texture);
		bool addToSlot(OpenGLTexture* texture);
		void clearSlots();
		void activateTextureSlots();

		~OpenGLTextureManager();
	};

	
}