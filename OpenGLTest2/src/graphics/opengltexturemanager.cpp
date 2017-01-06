#include "opengltexturemanager.h"

namespace VR {

	unsigned int OpenGLTextureManager::mTextureIDCount = 0;

	unsigned int OpenGLTextureManager::getNewTextureID() {
		unsigned int ID = mTextureIDCount;
		++mTextureIDCount;
		return ID;
	}

	void OpenGLTextureManager::add(OpenGLTexture* texture) {
		mTextures.push_back(texture);
	}

	bool OpenGLTextureManager::addToSlot(OpenGLTexture* texture) {
		if (mOccupiedSlots >= MAX_TEXTURE_SLOTS)
			return false;
		
		GLuint textureID = texture->getTextureID();

		if (mTextureSlots.find(textureID) != mTextureSlots.end())
			texture->unload();

		mTextureSlots[textureID] = texture->getOpenGLTextureID();

		++mOccupiedSlots;
		return true;
	}

	void OpenGLTextureManager::activateTextureSlots() {
		
		int i = 0;
		for (const auto& texture : mTextureSlots) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texture.second);
			++i;
		}
		
	}

	void OpenGLTextureManager::clearSlots() {
		mTextureSlots.clear();
	}

	OpenGLTextureManager::~OpenGLTextureManager() {
		for (auto& texture : mTextures)
			delete texture;
	}
}