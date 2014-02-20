#include "JGDITexture2D.h"
#include "Graphics/JImage.h"

JGDITexture2D::~JGDITexture2D()
{
	if(m_nName != 0)
		::DeleteObject((HGDIOBJ)m_nName);
}

bool JGDITexture2D::CreateFromImage(const JImage* pImg)
{
	int x = pImg->GetWidth();
	int y = pImg->GetHeight();
	uint8_t *pPixel = pImg->GetData();

	BITMAPINFO bmi;
	::ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = x;
	bmi.bmiHeader.biHeight = -y;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = x * y * 4;

	bool bAlphaChannel = false;
	LPBYTE pDest = NULL;
	HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pDest, NULL, 0);
	if( !hBitmap )
		return false;

	for( int i = 0; i < x * y; i++ ) 
	{
		pDest[i*4 + 3] = pPixel[i*4 + 3];
		if( pDest[i*4 + 3] < 255 )
		{
			pDest[i*4] = (BYTE)(DWORD(pPixel[i*4 + 2])*pPixel[i*4 + 3]/255);
			pDest[i*4 + 1] = (BYTE)(DWORD(pPixel[i*4 + 1])*pPixel[i*4 + 3]/255);
			pDest[i*4 + 2] = (BYTE)(DWORD(pPixel[i*4])*pPixel[i*4 + 3]/255); 
			bAlphaChannel = true;
		}
		else
		{
			pDest[i*4] = pPixel[i*4 + 2];
			pDest[i*4 + 1] = pPixel[i*4 + 1];
			pDest[i*4 + 2] = pPixel[i*4]; 
		}

		if( *(DWORD*)(&pDest[i*4]) == 0 ) {
			pDest[i*4] = (BYTE)0;
			pDest[i*4 + 1] = (BYTE)0;
			pDest[i*4 + 2] = (BYTE)0; 
			pDest[i*4 + 3] = (BYTE)0;
			bAlphaChannel = true;
		}
	}

	m_nName = (uint32_t)hBitmap;
	m_nWidth = x;
	m_nHeight = y;
	m_Format = pImg->GetPixelFormat();
	return true;
}
