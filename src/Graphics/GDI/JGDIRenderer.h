#ifndef JGDIRENDER_H_
#define JGDIRENDER_H_

#include <windows.h>
#include "Graphics/JRenderer.h"

#pragma comment(lib,"msimg32.lib")

class JGDIRenderer : public JRenderer
{
public:
	JGDIRenderer();

	void SetWindowHandler(HWND hWnd);

	virtual JTexture2D *CreateTexture(const char* filename);
	virtual JTexture2D *CreateTexture(const JImage* image);

	virtual bool BeginPaint();
	virtual bool EndPaint();
	virtual bool GetUpdateRect(JRectI& rect);

	virtual void DrawRect(const JRectI& rect, uint32_t color);
	virtual void DrawRectFill(const JRectI& rect, uint32_t color);

	virtual void DrawLine(const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color);
	virtual void DrawLine(int x1, int y1, int x2, int y2, uint32_t color);

	virtual void DrawImage(JTexture2D* img, const JPoint2I& pos);
	virtual void DrawImageSR(JTexture2D* img, const JPoint2I& pos, const JRectI& srcRect);
	virtual void DrawImageStretch(JTexture2D* img, const JRectI& destRect);
	virtual void DrawImageStretchSR(JTexture2D* img, const JRectI& destRect, const JRectI& srcRect);

private:
	HWND m_hWnd;
	PAINTSTRUCT m_PaintInfo;
	bool m_bBeginPaint;
	JRectI m_rcUpdateRect;
	HDC m_hBackDC;
	HBITMAP m_hBackBMP;
	HBITMAP m_hOldBMP;
};

#endif