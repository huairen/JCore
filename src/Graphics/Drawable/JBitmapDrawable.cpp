#include "JBitmapDrawable.h"
#include "Graphics/JTexture2D.h"

JBitmapDrawable::JBitmapDrawable()
	: m_pBitmap(0)
{

}

JBitmapDrawable::~JBitmapDrawable()
{
	if(m_pBitmap != 0)
		delete m_pBitmap;
}

void JBitmapDrawable::Draw()
{

}

