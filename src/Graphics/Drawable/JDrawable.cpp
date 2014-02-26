#include "JDrawable.h"
#include "JBitmapDrawable.h"
#include "JNinePatchDrawable.h"
#include "FileSystem/JFileSystem.h"

JDrawable::JDrawable()
{

}

JDrawable::~JDrawable()
{

}

JDrawable* JDrawable::Create(const char* pString)
{
	if(JFileSystem::GetInstance().IsFileExist(pString))
	{
		const char* ptr = strrchr(pString, '.');
		if(ptr && (ptr - pString > 2) && (*--ptr == '9') && (*--ptr == '.'))
		{
			JNinePatchDrawable* pBmp = new JNinePatchDrawable;
			if(pBmp != 0 && pBmp->Load(pString))
				return pBmp;

			delete pBmp;
		}
		else
		{
			JBitmapDrawable* pBmp = new JBitmapDrawable;
			if(pBmp != 0 && pBmp->Load(pString))
				return pBmp;

			delete pBmp;
		}

	}

	return 0;
}
