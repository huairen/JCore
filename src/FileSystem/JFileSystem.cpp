#include "JFileSystem.h"
#include <io.h>

JFileSystem::JFileSystem()
{

}

JFileSystem::~JFileSystem()
{

}

bool JFileSystem::IsFileExist(const char* pFileName)
{
	if(_access(pFileName, 0) != -1)
		return true;
	return false;
}