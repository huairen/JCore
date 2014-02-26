#include "JStateListDrawable.h"
#include "Graphics/JRenderSystem.h"

JStateListDrawable::JStateListDrawable()
	: m_pBitmap(0)
{

}

JStateListDrawable::~JStateListDrawable()
{
	if(m_pBitmap != 0)
		delete m_pBitmap;
}

void JStateListDrawable::Draw(const JRectI& rcOrigin, const JRectI& rcPaint)
{
	JRenderer* pRenderer = JRenderSystem::GetInstance().GetRenderer();
	if(pRenderer == NULL)
		return;

	float xScale = (float)m_pBitmap->GetWidth() / rcOrigin.extent.x;
	float yScale = (float)m_pBitmap->GetHeight() / rcOrigin.extent.y;

	JRectI imgRect;
	imgRect.position.x = (int)((rcPaint.position.x - rcOrigin.position.x) * xScale);
	imgRect.position.y = (int)((rcPaint.position.y - rcOrigin.position.y) * yScale);
	imgRect.extent.x = (int)(rcPaint.extent.x * xScale);
	imgRect.extent.y = (int)(rcPaint.extent.y * yScale);

	pRenderer->DrawImageStretchSR(m_pBitmap, rcPaint, imgRect);
}

bool JStateListDrawable::Load(const char* filename)
{
	m_pBitmap = JRenderSystem::GetInstance().CreateTexture(filename);
	return (m_pBitmap != NULL);
}

