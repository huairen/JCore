#ifndef JRENDER_SYSTEM_H_
#define JRENDER_SYSTEM_H_

#include "JRenderer.h"

class JRenderSystem
{
public:
	JRenderSystem();
	~JRenderSystem();

	static JRenderSystem& GetInstance()
	{
		static JRenderSystem instance;
		return instance;
	}

	bool CreateRenderer(const char* pName, uint32_t nHandler);
	inline JRenderer* GetRenderer() { return m_pRenderer; }

	inline JTexture2D* CreateTexture(const char* pFileName)
				{ return m_pRenderer->CreateTexture(pFileName); }
	inline JTexture2D* CreateTexture(const JImage* pImage)
				{ return m_pRenderer->CreateTexture(pImage); }

	inline bool BeginPaint() { return m_pRenderer->BeginPaint(); }
	inline bool EndPaint() { return m_pRenderer->EndPaint(); }
	inline bool GetUpdateRect(JRectI& rect) { return m_pRenderer->GetUpdateRect(rect); }

	inline void DrawRect(const JRectI& rect, uint32_t color)
				{ return m_pRenderer->DrawRect(rect, color); }
	inline void DrawRectFill(const JRectI& rect, uint32_t color)
				{ return m_pRenderer->DrawRectFill(rect, color); }

	inline void DrawLine(const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color)
				{ return m_pRenderer->DrawLine(startPt, endPt, color); }
	inline void DrawLine(int x1, int y1, int x2, int y2, uint32_t color)
				{ return m_pRenderer->DrawLine(x1, y1, x2, y2, color); }

	inline void DrawImage(JTexture2D* img, const JPoint2I& pos)
				{ return m_pRenderer->DrawImage(img, pos); }
	inline void DrawImageSR(JTexture2D* img, const JPoint2I& pos, const JRectI& srcRect)
				{ return m_pRenderer->DrawImageSR(img, pos, srcRect); }
	inline void DrawImageStretch(JTexture2D* img, const JRectI& destRect)
				{ return m_pRenderer->DrawImageStretch(img, destRect); }
	inline void DrawImageStretchSR(JTexture2D* img, const JRectI& destRect, const JRectI& srcRect)
				{ return m_pRenderer->DrawImageStretchSR(img, destRect, srcRect); }

private:
	JRenderer* m_pRenderer;
};

#endif
