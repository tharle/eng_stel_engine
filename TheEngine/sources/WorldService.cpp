#include "WorldService.h"

void WorldService::Add(Entity* entity)
{
	// TODO valider si le nom existe dej� dans le map
	m_Entities.emplace_back(entity)
	//m_EntityMap.insert(ent->GetName(), ent);
}

Entity* WorldService::Find(const char* name)
{
	for (Entity* entity : m_Entities) 
	{
		if (entity->GetName() == name) return entity;
	}

	return nullptr;
}

void WorldService::Remove(Entity* ent)
{
	//m_EntityMap.erase(ent);
	/*for (auto it = m_EntityMap.end(); it != m_EntityMap.begin();it--)
	{
		(*it).
	}*/
}

void WorldService::LoadScene(const char* sceneName)
{
}

void WorldService::Register(const char* name, IScene* scene)
{
}

void WorldService::Update(float dt)
{
	for(Entity entity : m_EntityMap)
	{
		entity->Update(dt);
	}
}

void WorldService::Draw()
{
	for(Entity entity : m_EntityMap)
	{
		entity->Drawn();
	}
}
