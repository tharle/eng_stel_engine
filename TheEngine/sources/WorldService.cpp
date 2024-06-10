#include "WorldService.h"

void WorldService::Add(Entity* ent)
{
	// TODO valider si le nom existe dejà dans le map

	m_Entities.push_back(ent);
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
	/*for(Entity entity : m_EntityMap)
	{

	}*/
}

void WorldService::Draw()
{
}
