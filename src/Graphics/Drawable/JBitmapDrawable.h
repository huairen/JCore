#ifndef JBITMAP_DRAWABLE_H_
#define JBITMAP_DRAWABLE_H_

#include "JDrawable.h"

class JTexture2D;

class JBitmapDrawable : public JDrawable
{
public:
	JBitmapDrawable();
	virtual ~JBitmapDrawable();

	virtual void Draw();

protected:
	JTexture2D* m_pBitmap;
};
#endif //JBITMAP_DRAWABLE_H_