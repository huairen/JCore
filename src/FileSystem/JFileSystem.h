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

	bool IsFileExist(const char* pFileName);
};

#endif