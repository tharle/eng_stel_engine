#include "Chest.h"
#include "StelAtlas.h"
#include "PlayerControls.h"

void Chest::Start()
{
	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init("Assets/adv_lolo_map.png");
	m_Model->AddFrame({ 2 * 16, 3 * 16, 16, 16 });
	m_Model->AddFrame({ 3 * 16, 2 * 16, 16, 16 });
	m_Model->AddFrame({ 3 * 16, 3 * 16, 16, 16 });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Chest::Update(float dt)
{
	if (Input().IsKeyDown(IInput::H)) 
	{
		m_Model->SetFrame(1);
		m_IsOpen = true;

	}

	if (m_IsOpen) {
		if (Physic().CollideWithLayer(m_EntityParent, PlayerControls::Layer()) != nullptr)
		{
			m_Model->SetFrame(2);
		}
	}
}