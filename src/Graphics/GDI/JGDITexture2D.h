#ifndef JGDIIMAGE_H_
#define JGDIIMAGE_H_

#include <windows.h>
#include "Graphics/JTexture2D.h"

class JGDITexture2D : public JTexture2D
{
public:
	virtual ~JGDITexture2D();
	virtual bool CreateFromImage(const JImage* pImg);
};

#endif