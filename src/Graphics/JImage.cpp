#include "JImage.h"  

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
	, m_FileType(UNKOWN)
	, m_PixelFormat(NONE)
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
	fseek(pFile, 0, SEEK_END);
	int nSize = ftell(pFile);

	uint8_t *pData = (uint8_t*)malloc(nSize);
	fread(pData, sizeof(uint8_t), nSize, pFile);

	bool bResult = LoadFromImageData(pData, nSize);
	free(pData);

	return bResult;
}

bool JImage::LoadFromImageData(const uint8_t* pData, uint32_t nSize)
{
	m_pData = stbi_load_from_memory(pData, nSize, &m_nWidth, &m_nHeight, NULL, 4);
	return m_pData != NULL;
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
