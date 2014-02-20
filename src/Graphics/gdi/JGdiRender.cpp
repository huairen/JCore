#include "JGdiRender.h"
#include "JGdiTexture2D.h"
#include "Graphics/JImage.h"

JGDIRender::JGDIRender()
{
	m_hWnd = NULL;
	m_hBackDC = NULL;
	m_hBackBMP = NULL;
	m_hOldBMP = NULL;
	m_bBeginPaint = false;
}

void JGDIRender::SetWindowHandler( HWND hWnd )
{
	m_hWnd = hWnd;
}

JTexture2D * JGDIRender::CreateTexture( const char* filename )
{
	JGDITexture2D *texture = new JGDITexture2D;
	if(texture->CreateFromFile(filename))
		return texture;

	delete texture;
	return NULL;
}

bool JGDIRender::BeginPaint()
{
	RECT rcPaint;
	if(!::GetUpdateRect(m_hWnd, &rcPaint, FALSE))
		return false;

	m_rcUpdateRect.position.x = rcPaint.left;
	m_rcUpdateRect.position.y = rcPaint.top;
	m_rcUpdateRect.extent.x = rcPaint.right - rcPaint.left;
	m_rcUpdateRect.extent.y = rcPaint.bottom - rcPaint.top;

	::BeginPaint(m_hWnd, &m_PaintInfo);

	m_hBackDC = ::CreateCompatibleDC(m_PaintInfo.hdc);
	m_hBackBMP = ::CreateCompatibleBitmap(m_PaintInfo.hdc, m_rcUpdateRect.extent.x, m_rcUpdateRect.extent.y); 
	m_hOldBMP =  (HBITMAP)::SelectObject(m_hBackDC, m_hBackBMP);

	m_bBeginPaint = true;
	return true;
}

bool JGDIRender::EndPaint()
{
	//»æÖÆ°ëÍ¸Ã÷µ×Í¼
/*	{
		static BLENDFUNCTION blendFunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};

		DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
		if((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
			SetWindowLong(m_hWnd, GWL_EXSTYLE, (dwExStyle | WS_EX_LAYERED));

		RECT rcWindow;
		::GetWindowRect(m_hWnd, &rcWindow);

		POINT dstPos = {rcWindow.left, rcWindow.top};
		SIZE dstSize = {rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top};
		POINT srcPos = {0, 0};

		HDC hdcTemp = ::GetWindowDC(m_hWnd);

		UpdateLayeredWindow(m_hWnd, hdcTemp, &dstPos, &dstSize, m_hBackDC, &srcPos, 0, &blendFunc, ULW_ALPHA);
		::ReleaseDC(m_hWnd, hdcTemp);
	}*/

	::BitBlt(m_PaintInfo.hdc, m_rcUpdateRect.position.x, m_rcUpdateRect.position.y,
		m_rcUpdateRect.extent.x, m_rcUpdateRect.extent.y, m_hBackDC, 0, 0, SRCCOPY);

	::SelectObject(m_hBackDC, m_hOldBMP);
	::DeleteObject(m_hBackBMP);
	::DeleteObject(m_hBackDC);

	m_bBeginPaint = false;
	::EndPaint(m_hWnd, &m_PaintInfo);
	return true;
}

bool JGDIRender::GetUpdateRect( JRectI& rect )
{
	if(!m_bBeginPaint)
		return false;

	rect = m_rcUpdateRect;
	return true;
}


void JGDIRender::DrawRect( const JRectI& rect, uint32_t color )
{

}

void JGDIRender::DrawRectFill( const JRectI& rect, uint32_t color )
{

}

void JGDIRender::DrawLine( const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color )
{

}

void JGDIRender::DrawLine( int x1, int y1, int x2, int y2, uint32_t color )
{

}

void JGDIRender::DrawImage( JTexture2D* img, const JPoint2I& pos )
{
	HBITMAP hBmp = (HBITMAP)img->GetName();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	::BitBlt(m_hBackDC, pos.x - m_rcUpdateRect.position.x,
		pos.y - m_rcUpdateRect.position.x, img->GetWidth(),
		img->GetHeight(), hSrcDc, 0, 0, SRCCOPY);

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}

void JGDIRender::DrawImageSR( JTexture2D* img, const JPoint2I& pos, const JRectI& srcRect )
{
	HBITMAP hBmp = (HBITMAP)img->GetName();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	::StretchBlt(m_hBackDC, pos.x - m_rcUpdateRect.position.x,
		pos.y - m_rcUpdateRect.position.x, img->GetWidth(), img->GetHeight(), 
		hSrcDc, srcRect.position.x, srcRect.position.y, srcRect.extent.x, srcRect.extent.y, SRCCOPY);

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}

void JGDIRender::DrawImageStretch( JTexture2D* img, const JRectI& destRect )
{
	HBITMAP hBmp = (HBITMAP)img->GetName();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	::BitBlt(m_hBackDC, destRect.position.x - m_rcUpdateRect.position.x,
		destRect.position.y - m_rcUpdateRect.position.y, destRect.extent.x,
		destRect.extent.y, hSrcDc, 0, 0, SRCCOPY);

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}

void JGDIRender::DrawImageStretchSR( JTexture2D* texture, const JRectI& destRect, const JRectI& srcRect )
{
	HBITMAP hBmp = (HBITMAP)texture->GetName();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	if(texture->HasAlphaChannel())
	{
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		::AlphaBlend(m_hBackDC, destRect.position.x - m_rcUpdateRect.position.x,
			destRect.position.y - m_rcUpdateRect.position.y, destRect.extent.x, destRect.extent.y,
			hSrcDc, srcRect.position.x, srcRect.position.y, srcRect.extent.x, srcRect.extent.y, bf);
	}
	else
	{
		::StretchBlt(m_hBackDC, destRect.position.x - m_rcUpdateRect.position.x,
			destRect.position.y - m_rcUpdateRect.position.y, destRect.extent.x, destRect.extent.y, 
			hSrcDc, srcRect.position.x, srcRect.position.y, srcRect.extent.x, srcRect.extent.y, SRCCOPY);
	}

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}