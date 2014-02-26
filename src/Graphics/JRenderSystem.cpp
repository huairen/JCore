#include "JRenderSystem.h"
#include "GDI/JGDIRenderer.h"

JRenderSystem::JRenderSystem()
	: m_pRenderer(0)
{

}

JRenderSystem::~JRenderSystem()
{

}

bool JRenderSystem::CreateRenderer(const char* pName, uint32_t nHandler)
{
	if(stricmp(pName, "gdi") == 0)
	{
		JGDIRenderer* pGDI = new JGDIRenderer();
		if(pGDI == NULL)
			return false;

		pGDI->SetWindowHandler((HWND)nHandler);
		m_pRenderer = pGDI;
	}

	return true;
}

JTexture2D* JRenderSystem::CreateTexture(const char* pFileName)
{
	if(m_pRenderer != NULL)
		return m_pRenderer->CreateTexture(pFileName);
	return NULL;
}

JTexture2D* JRenderSystem::CreateTexture(const JImage* pImage)
{
	if(m_pRenderer != NULL)
		return m_pRenderer->CreateTexture(pImage);
	return NULL;
}
