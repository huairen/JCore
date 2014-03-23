#ifndef JIMAGE_H_
#define JIMAGE_H_

#include "JGlobalDefine.h"
#include "JTexture2D.h"

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

public:
	JImage();
	virtual ~JImage();

	bool LoadFromFile(const char* pFilename);
	bool LoadFromImageData(const uint8_t* pData, uint32_t nSize);

	uint32_t GetPixel(uint32_t x, uint32_t y) const;

	inline uint8_t* GetData() const { return m_pData; }
	inline uint32_t GetDataLen() const { return m_nDataSize; }
	inline uint32_t GetWidth() const { return m_nWidth; }
	inline uint32_t GetHeight() const { return m_nHeight; }
	inline JTexture2D::PixelFormat GetPixelFormat() const { return m_PixelFormat; }

private:
	FileFormat DetectFormat(const uint8_t* pData, uint32_t nSize);
	bool CheckPngHeader(const uint8_t* pData, uint32_t nSize);
	bool CheckJpgHeader(const uint8_t* pData, uint32_t nSize);

protected:
	uint8_t *m_pData;
	uint32_t m_nDataSize;

	uint32_t m_nWidth;
	uint32_t m_nHeight;
	uint32_t m_nPixelByte;

	FileFormat m_FileType;
	JTexture2D::PixelFormat m_PixelFormat;

	bool m_bAlphaChannel;
	std::string m_FilePath;
};


#endif
                                                  