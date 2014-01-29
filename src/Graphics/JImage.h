#ifndef JIMAGE_H_
#define JIMAGE_H_

#include "JGlobalDefine.h"

class JImage
{
public:
	enum FileFormat
	{
		UNKOWN,
		JPEG,
		PNG,
		BMP,
		GIF,
	};

	enum PixelFormat
	{
		NONE,

		A8,
		L8,

		R8G8B8,
		R8G8B8A8,
	};

public:
	JImage();
	virtual ~JImage();

	virtual bool Load(const char* filename) = 0;
	virtual int GetHandler() = 0;

	bool LoadFromFile(const char* pFilename);
	bool LoadFromImageData(const uint8_t* pData, uint32_t nSize);

	inline int GetWidth() { return m_nWidth;}
	inline int GetHeight() { return m_nHeight; }
	inline bool HasAlphaChannel() { return m_bAlphaChannel; }

private:
	FileFormat DetectFormat(const uint8_t* pData, uint32_t nSize);
	bool CheckPngHeader(const uint8_t* pData, uint32_t nSize);
	bool CheckJpgHeader(const uint8_t* pData, uint32_t nSize);

protected:
	uint8_t *m_pData;
	uint32_t m_nDataSize;

	int m_nWidth;
	int m_nHeight;

	FileFormat m_FileType;
	PixelFormat m_PixelFormat;

	bool m_bAlphaChannel;
	std::string m_FilePath;
};


#endif
                                                  