#include "JFileSystem.h"
#include "JGlobalDefine.h"
#include "String/JStringFunction.h"
#include <windows.h>
#include <sys/stat.h>

JFileSystem::JFileSystem()
{
	m_szRootDirectory[0] = 0;
	m_szCurrentPath[0] = 0;
}

JFileSystem::~JFileSystem()
{

}

void JFileSystem::SetResourcePath(const char* pPath)
{
}

void JFileSystem::SetCurrentPath(const char* pPath)
{
	m_szCurrentPath[0] = 0;
	EnterPath(pPath);
}

void JFileSystem::EnterPath(const char* pPath)
{
	if(pPath == NULL)
		return;

	if(m_szRootDirectory[0] == 0)
	{
		::GetCurrentDirectory(sizeof(m_szRootDirectory), m_szRootDirectory);
		JStringFunction::ForwardSlash(m_szRootDirectory);
	}

	char szBuff[256];
	MakeFullPath(pPath, szBuff, sizeof(szBuff));
	if(IsFileExist(szBuff))
	{
		char* ptr = strrchr(szBuff, '/');
		if(ptr != NULL)
			*ptr = 0;
	}

	if(IsDirectory(szBuff))
		strncpy(m_szCurrentPath, szBuff, sizeof(m_szCurrentPath));
}

bool JFileSystem::MakeFullPath(const char *file, char *fullpath, int size)
{
	char bspath[256];
	strncpy(bspath, file, sizeof(bspath));
	bspath[sizeof(bspath)-1] = 0;

	JStringFunction::ForwardSlash(bspath);

	if(bspath[0] == '/' || bspath[1] == ':')
	{
		strncpy(fullpath, bspath, size);
		fullpath[size - 1] = 0;
		return true;
	}

	if(m_szCurrentPath[0] != 0)
 		strncpy(fullpath, m_szCurrentPath, size);
	else
		strncpy(fullpath, m_szRootDirectory, size);


	char *ptr = bspath;
	char *slash = NULL;
	char *endptr = fullpath + strlen(fullpath) - 1;

	do 
	{
		slash = strchr(ptr, '/');
		if(slash)
		{
			*slash = 0;
			if(strcmp(ptr, "..") == 0)
			{
				if(fullpath[0] == 0)	//当前路径为空，直接拷贝
				{
					*slash = '/';
					strcpy_s(fullpath, size, ptr);
					return true;
				}

				//当前路径退后一个目录
				endptr = strrchr(fullpath, '/');
				if(endptr == 0)
				{
// 					endptr = buffer;
// 					*endptr = 0;
					return false;	//已经到根目录，返回错误
				}
				else
				{
					*endptr-- = 0;
				}
			}
			else if(strcmp(ptr, ".") == 0)
			{
				//current dir
			}
			else if(endptr)
			{
				if(*endptr != '/')
				{
					endptr[1] = '/';
					endptr[2] = '\0';
				}
				strcat(endptr, ptr);
				endptr += strlen(endptr) - 1;
			}

			ptr = slash + 1;
		}
		else if(endptr)
		{
			if(*endptr != '/')
			{
				endptr[1] = '/';
				endptr[2] = '\0';
			}
			strcat(endptr, ptr);
			endptr += strlen(endptr) - 1;
		}

	} while (slash);

	return true;
}


bool JFileSystem::IsFileExist(const char* pFileName)
{
	struct stat fileStat;
	if(stat(pFileName, &fileStat) == -1)
		return false;
	
	return !(fileStat.st_mode & S_IFDIR);
}

bool JFileSystem::IsDirectory(const char* pPath)
{
	struct stat fileStat;
	if(stat(pPath, &fileStat) == -1)
		return false;

	return ((fileStat.st_mode & S_IFDIR) != 0);
}
