#ifndef JSTATELIST_DRAWABLE_H_
#define JSTATELIST_DRAWABLE_H_

#include "JDrawable.h"

class JTexture2D;

class JStateListDrawable : public JDrawable
{
public:
	JStateListDrawable();
	virtual ~JStateListDrawable();

	virtual void Draw(const JRectI& rcOrigin, const JRectI& rcPaint);

	bool Load(const char* filename);

protected:
	JTexture2D* m_pBitmap;
};
#endif //JBITMAP_DRAWABLE_H_