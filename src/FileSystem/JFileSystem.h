#ifndef JFILE_SYSTEM_H_
#define JFILE_SYSTEM_H_

class JFileSystem
{
public:
	JFileSystem();
	~JFileSystem();

	static JFileSystem& GetInstance()
	{
		static JFileSystem instance;
		return instance;
	}

	void SetResourcePath(const char* pPath);
	void SetCurrentPath(const char* pPath);
	void EnterPath(const char* pPath);

	bool MakeFullPath( const char *file, char *fullpath, int size );

	bool IsFileExist(const char* pFileName);
	bool IsDirectory(const char* pPath);


private:
	char m_szRootDirectory[256];
	char m_szCurrentPath[256];
};

#endif