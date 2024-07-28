#include "Door.h"
#include "StelAtlas.h"
#include "PlayerControls.h"

void Door::Start(std::string spriteSheet, std::string nextScene)
{
	StelComponent::Start();

	m_NextScene = nextScene;

	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init(spriteSheet);
	StelPointI size = StelPointI::FromFloat(m_EntityParent->GetTransform().Size.x, m_EntityParent->GetTransform().Size.y);
	m_Model->AddFrame({ 4 * size.x, 4 * size.y, size.x, size.y });
	m_Model->AddFrame({ 5 * size.x, 4 * size.y, size.x, size.y });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Door::Update(float dt)
{
	if (!m_IsOpen) return;
	
	if (Physic().CollideWithLayer(m_EntityParent, PlayerControls::Layer()) != nullptr)
	{
		// Change scene
		World().LoadScene(m_NextScene);
	}
}

void Door::OnNotify(const bool& value)
{
	m_IsOpen = value;
	if (m_IsOpen) m_Model->SetFrame(1);
}
