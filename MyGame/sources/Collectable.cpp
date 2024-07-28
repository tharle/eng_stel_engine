#include "Collectable.h"
#include "StelAtlas.h"
#include "PlayerControls.h"

void Collectable::Start()
{
	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init("Assets/adv_lolo_map.png");
	StelPointI size = StelPointI::FromFloat(m_EntityParent->GetTransform().Size.x, m_EntityParent->GetTransform().Size.y);
	m_Model->AddFrame({ 1 * size.x, 3 * size.y, size.x, size.y });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Collectable::Update(float dt)
{
	StelEntity* other = Physic().CollideWithLayer(m_EntityParent, PlayerControls::Layer());
	if (other != nullptr) 
	{
		OnItem.Invoke(true);
		m_EntityParent->Destroy();
	}
}
