#include "JImage.h"
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif
	extern uint8_t *stbi_load_from_memory(uint8_t const *buffer, int len, int *x, int *y, int *comp, int req_comp);
#ifdef __cplusplus
}
#endif

JImage::JImage()
	: m_pData(0)
	, m_nDataSize(0)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nPixelByte(0)
	, m_FileType(UNKOWN)
	, m_PixelFormat(JTexture2D::NONE)
	, m_bAlphaChannel(false)
{

}

JImage::~JImage()
{
	if(m_pData != NULL)
		free(m_pData);
}

bool JImage::LoadFromFile(const char* pFilename)
{
	FILE *pFile = fopen(pFilename, "rb");
	if(pFile == NULL)
		return false;

	fseek(pFile, 0, SEEK_END);
	int nSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	uint8_t *pData = (uint8_t*)malloc(nSize);
	fread(pData, sizeof(uint8_t), nSize, pFile);

	bool bResult = LoadFromImageData(pData, nSize);
	free(pData);

	return bResult;
}

bool JImage::LoadFromImageData(const uint8_t* pData, uint32_t nSize)
{
	int x,y,n;
	m_pData = stbi_load_from_memory(pData, nSize, &x, &y, &n, 4);

	m_nWidth = x;
	m_nHeight = y;
	m_nPixelByte = n;

	if(m_nPixelByte == 4)
		m_PixelFormat = JTexture2D::R8G8B8A8;
	else if(m_nPixelByte == 3)
		m_PixelFormat = JTexture2D::R8G8B8;

	return m_pData != NULL;
}

uint32_t JImage::GetPixel(uint32_t x, uint32_t y) const
{
	if(x >= m_nWidth || y >= m_nHeight)
		return 0;
	return *(int*)(m_pData + (m_nWidth * y * m_nPixelByte) + (x * m_nPixelByte));
}

JImage::FileFormat JImage::DetectFormat(const uint8_t* pData, uint32_t nSize)
{
	return UNKOWN;
}

bool JImage::CheckPngHeader(const uint8_t* pData, uint32_t nSize)
{
	static uint8_t png_sig[8] = { 137,80,78,71,13,10,26,10 };
	if(nSize <= sizeof(png_sig))
		return false;

	return memcmp(png_sig, pData, sizeof(png_sig)) == 0;
}

bool JImage::CheckJpgHeader(const uint8_t* pData, uint32_t nSize)
{
	return false;
}
