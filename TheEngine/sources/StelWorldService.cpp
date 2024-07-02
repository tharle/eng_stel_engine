#include "StelWorldService.h"

StelEntity* StelWorldService::Create(const char* name)
{
	StelEntity* ent = new StelEntity(name);
	m_EntityInWorld.push_back(ent);
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
	if (m_SceneMap.count(sceneName) > 0) {
		m_SceneMap[sceneName]->Load();
	}

}

void StelWorldService::UnLoad()
{
	if (m_CurrentScene != nullptr) {
		for (auto entity : m_EntityInWorld) {
			entity->Destroy();
			delete entity;
		}
		m_EntityInWorld.clear();
		m_EntityMap.clear();
	}
}

void StelWorldService::Register(const char* sceneName, IScene* scene)
{
	if (m_SceneMap.count(sceneName) == 0) {
		m_SceneMap[sceneName] = scene;
	}

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
