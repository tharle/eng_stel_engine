#include "Collectable.h"
#include "StelAtlas.h"

void Collectable::Start()
{
	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init("Assets/adv_lolo_map.png");
	m_Model->AddFrame({ 1 * 16, 3 * 16, 16, 16 });
	m_Model->AddFrame({ 0 * 16, 1 * 16, 16, 16 });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Collectable::Update(float dt)
{
}
