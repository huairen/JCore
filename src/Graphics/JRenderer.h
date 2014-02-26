#ifndef JRENDERER_H_
#define JRENDERER_H_

#include "JGlobalDefine.h"
#include "JTexture2D.h"
#include "math/JRect.h"

class JRenderer
{
public:
	virtual JTexture2D *CreateTexture(const char* filename) = 0;
	virtual JTexture2D *CreateTexture(const JImage* image) = 0;

	virtual bool BeginPaint() = 0;
	virtual bool EndPaint() = 0;
	virtual bool GetUpdateRect(JRectI& rect) { return false; }

	virtual void DrawRect(const JRectI& rect, uint32_t color) = 0;
	virtual void DrawRectFill(const JRectI& rect, uint32_t color) = 0;

	virtual void DrawLine(const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color) = 0;
	virtual void DrawLine(int x1, int y1, int x2, int y2, uint32_t color) = 0;

	virtual void DrawImage(JTexture2D* img, const JPoint2I& pos) = 0;
	virtual void DrawImageSR(JTexture2D* img, const JPoint2I& pos, const JRectI& srcRect) = 0;
	virtual void DrawImageStretch(JTexture2D* img, const JRectI& destRect) = 0;
	virtual void DrawImageStretchSR(JTexture2D* img, const JRectI& destRect, const JRectI& srcRect) = 0;
};

#endif
