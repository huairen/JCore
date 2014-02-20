#ifndef JDRAWABLE_H_
#define JDRAWABLE_H_

class JDrawable
{
public:
	virtual ~JDrawable() = 0;
	virtual void Draw() = 0;

	static JDrawable* Create(const char* pString);
};

#endif // !JDRAWABLE_H_
