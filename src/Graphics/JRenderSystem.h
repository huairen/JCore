#ifndef JRENDER_SYSTEM_H_
#define JRENDER_SYSTEM_H_

#include "JRenderer.h"

class JRenderSystem
{
public:
	JRenderSystem();
	~JRenderSystem();

	static JRenderSystem& GetInstance()
	{
		static JRenderSystem instance;
		return instance;
	}

	bool CreateRenderer(const char* pName, uint32_t nHandler);

	JTexture2D* CreateTexture(const char* pFileName);
	JTexture2D* CreateTexture(const JImage* pImage);



	inline JRenderer* GetRenderer() { return m_pRenderer; }


private:
	JRenderer* m_pRenderer;
};

#endif
