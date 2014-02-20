#ifndef JTEXTURE2D_H_
#define JTEXTURE2D_H_

#include "JGlobalDefine.h"

class JImage;

class JTexture2D
{
public:
	enum PixelFormat
	{
		NONE,

		A8,
		L8,

		R8G8B8,
		R8G8B8A8,
	};

public:
	JTexture2D();
	virtual ~JTexture2D();

	bool CreateFromFile(const char* pFilename);
	virtual bool CreateFromImage(const JImage* pImg) = 0;

	inline uint32_t GetName() { return m_nName; }
	inline uint32_t GetWidth() { return m_nWidth; }
	inline uint32_t GetHeight() { return m_nHeight; }

	bool HasAlphaChannel();

protected:
	uint32_t m_nName;
	uint32_t m_nWidth;
	uint32_t m_nHeight;
	PixelFormat m_Format;
};


#endif
                                                  