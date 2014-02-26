#include "JStringFunction.h"
#include <string>

char* JStringFunction::Trim(char* src)
{
	return TrimRight(TrimLeft(src));
}

char* JStringFunction::TrimLeft(char* src)
{
	char* cp = 0;

	if(src == 0)
		return 0;

	if(src[0] == 0)
		return src;

	for (cp = src; isspace(*(unsigned char*)cp); ++cp);

	return cp;
}

char* JStringFunction::TrimRight(char* src)
{
	char* cp = 0;

	if(src == 0)
		return 0;

	if(src[0] == 0)
		return src;

	for (cp = src + strlen(src) - 1; cp != src; --cp)
		if(!isspace(*(unsigned char*)cp))
			break;
	cp[1] = '\0';

	return src;
}

