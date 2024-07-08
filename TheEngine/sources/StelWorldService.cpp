#include "StelWorldService.h"

StelEntity* StelWorldService::Create(std::string name)
{
	StelEntity* ent = new StelEntity(name);
	m_EntityInWorld.push_back(ent);
	m_EntityMap.emplace(name, ent);

	return ent;
}

StelEntity* StelWorldService::Find(std::string name)
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

void StelWorldService::LoadScene(std::string sceneName)
{
	if (m_SceneMap.count(sceneName) > 0) {
		UnLoad();
		m_CurrentScene = m_SceneMap[sceneName];
		m_CurrentScene->Load();
	}

}

void StelWorldService::UnLoad()
{
	if (m_CurrentScene != nullptr) {
		/*for (StelEntity* entity : m_EntityInWorld) {
			if (entity != nullptr){
				entity->Destroy();
				delete entity;
			}
		}*/
		delete m_CurrentScene;
		m_CurrentScene = nullptr;

		m_EntityInWorld.clear();
		m_EntityMap.clear();
	}
}

void StelWorldService::Register(std::string sceneName, IScene* scene)
{
	if (m_SceneMap.count(sceneName) == 0) {
		m_SceneMap[sceneName] = scene;
	}

}

void StelWorldService::Add(StelEntity* entity)
{
	m_EntityInWorld.push_back(entity);
	m_EntityMap[entity->GetName()] = entity;
}

void StelWorldService::Update(float dt)
{
	for (std::map<std::string, StelEntity*>::iterator it = m_EntityMap.begin(); it != m_EntityMap.end(); it++)
	{
		StelEntity* entity = it->second;	
		if (entity != nullptr) entity->Update(dt);
	}
}

void StelWorldService::Draw()
{
	for (std::map<std::string, StelEntity*>::iterator it = m_EntityMap.begin(); it != m_EntityMap.end(); it++)
	{
		StelEntity* entity = it->second;
		if (entity != nullptr) entity->Draw();
	}
}
