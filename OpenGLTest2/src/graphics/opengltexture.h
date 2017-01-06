#pragma once
#include "texture.h"
#include <FreeImage/FreeImage.h>
#include <GL/glew.h>

namespace VR {

	class OpenGLTexture : public Texture {
	private:
		GLuint mOpenGLTextureID;
		FIBITMAP* mFreeImageBitmap = nullptr;

	public:
		OpenGLTexture(const char* fileName, const unsigned int textureID);
		bool load() override;
		bool unload() override;
		void generateTexture();
		void bind();
		GLuint getOpenGLTextureID();
		
		~OpenGLTexture();
	};
}