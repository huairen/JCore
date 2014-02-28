#ifndef JSTRING_FUNCTION_H_
#define JSTRING_FUNCTION_H_


class JStringFunction
{
public:
	static char* Trim(char* src);
	static char* TrimLeft(char* src);
	static char* TrimRight(char* src);
	static void ForwardSlash(char* path);
};

#endif