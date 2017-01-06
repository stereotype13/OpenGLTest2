#include "opengltexture.h"

namespace VR {

	OpenGLTexture::OpenGLTexture(const char* fileName, const unsigned int textureID) {
		mFileName = fileName;
		mTextureID = textureID;
		mWidth = 0;
		mHeight = 0;
	}

	bool OpenGLTexture::load() {

		if (mFreeImageBitmap) {
			FreeImage_Unload(mFreeImageBitmap);
			mFreeImageBitmap = nullptr;
		}
		
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		//check the fiel signature and deduce its format
		fif = FreeImage_GetFileType(mFileName, 0);

		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(mFileName);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			mFreeImageBitmap = FreeImage_Load(fif, mFileName);
		//if the image failed to load, return failure
		if (!mFreeImageBitmap)
			return false;

		//retrieve the image data
		mData = FreeImage_GetBits(mFreeImageBitmap);
		//get the image width and height
		mWidth = FreeImage_GetWidth(mFreeImageBitmap);
		mHeight = FreeImage_GetHeight(mFreeImageBitmap);

		//if this somehow one of these failed (they shouldn't), return failure
		if ((mData == 0) || (mWidth == 0) || (mHeight == 0))
			return false;

		glGenTextures(1, &mOpenGLTextureID);
			

		return true;
	}

	bool  OpenGLTexture::unload() {
		glDeleteTextures(1, &mOpenGLTextureID);
		return true;
	}

	void OpenGLTexture::generateTexture() {
		glGenTextures(1, &mOpenGLTextureID);
	}

	OpenGLTexture::~OpenGLTexture() {
		if (mFreeImageBitmap) {
			FreeImage_Unload(mFreeImageBitmap);
			mFreeImageBitmap = nullptr;
		}
	}

	void OpenGLTexture::bind() {
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	GLuint OpenGLTexture::getOpenGLTextureID() {
		return mOpenGLTextureID;
	}
}