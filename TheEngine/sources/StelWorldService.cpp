#include "StelWorldService.h"

StelEntity* StelWorldService::Create(const char* name)
{
	StelEntity* ent = new StelEntity(name);
	m_EntityMap.emplace(name, ent);

	return ent;
}

StelEntity* StelWorldService::Find(const char* name)
{
	return m_EntityMap.at(name);
}

void StelWorldService::Remove(StelEntity* ent)
{
	//m_EntityMap.erase(ent);
	/*for (auto it = m_EntityMap.end(); it != m_EntityMap.begin();it--)
	{
		(*it).
	}*/
}

void StelWorldService::LoadScene(const char* sceneName)
{
}

void StelWorldService::Register(const char* name, IScene* scene)
{
}

void StelWorldService::Update(float dt)
{
	for (std::map<const char*, StelEntity*>::iterator it = m_EntityMap.begin(); it != m_EntityMap.end(); it++)
	{
		StelEntity* entity = it->second;	
		if (entity != nullptr) entity->Update(dt);
	}
}

void StelWorldService::Draw()
{
	for (std::map<const char*, StelEntity*>::iterator it = m_EntityMap.begin(); it != m_EntityMap.end(); it++)
	{
		StelEntity* entity = it->second;
		if (entity != nullptr) entity->Draw();
	}
}
