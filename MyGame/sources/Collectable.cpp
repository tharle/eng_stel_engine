#include "Collectable.h"
#include "StelAtlas.h"
#include "PlayerControls.h"

void Collectable::Start(char* spriteSheet, StelPointI frame)
{
	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init(spriteSheet);
	StelPointI size = StelPointI::FromFloat(m_EntityParent->GetTransform().Size.x, m_EntityParent->GetTransform().Size.y);
	m_Model->AddFrame({ frame.x * size.x, frame.y * size.y, size.x, size.y });
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
