#include "JTexture2D.h"
#include "JImage.h"

JTexture2D::JTexture2D()
	: m_nName(0)
	, m_nWidth(0)
	, m_nHeight(0)
{

}

JTexture2D::~JTexture2D()
{

}

bool JTexture2D::CreateFromFile(const char* pFilename)
{
	JImage img;
	if(!img.LoadFromFile(pFilename))
		return false;

	return CreateFromImage(&img);
}

bool JTexture2D::HasAlphaChannel()
{
	return (m_Format == R8G8B8A8);
}
