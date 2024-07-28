#include "Chest.h"
#include "StelAtlas.h"
#include "PlayerControls.h"

void Chest::Start(int chestAmount)
{
	StelComponent::Start();

	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_ChestAmount = chestAmount;
	m_Model->Init("Assets/adv_lolo_map.png");
	StelPointI size = StelPointI::FromFloat(m_EntityParent->GetTransform().Size.x, m_EntityParent->GetTransform().Size.y);
	m_Model->AddFrame({ 2 * size.x, 3 * size.y, size.x, size.y });
	m_Model->AddFrame({ 3 * size.x, 2 * size.y, size.x, size.y });
	m_Model->AddFrame({ 3 * size.x, 3 * size.y, size.x, size.y });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Chest::Update(float dt)
{
	if (!IsOpen()) return;

	if (Physic().CollideWithLayer(m_EntityParent, PlayerControls::Layer()) != nullptr)
	{
		m_Model->SetFrame(2);
		OnGetPearl.Invoke(true);
	}
	
}

bool Chest::IsOpen() {
	return m_CountHeartsTakes >= m_ChestAmount;
}

void Chest::OnNotify(const bool& value)
{
	if(value) m_CountHeartsTakes++;

	if(IsOpen()) m_Model->SetFrame(1);
}
