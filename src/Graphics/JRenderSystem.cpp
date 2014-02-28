#include "JRenderSystem.h"
#include "GDI/JGDIRenderer.h"

JRenderSystem::JRenderSystem()
	: m_pRenderer(0)
{

}

JRenderSystem::~JRenderSystem()
{
	if(m_pRenderer != NULL)
		delete m_pRenderer;
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