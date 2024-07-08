#include "StelWorldService.h"

StelWorldService::~StelWorldService()
{
	//if(m_EntityMap.)

	UnLoad();
	
	for (auto it = m_SceneMap.end(); it != m_SceneMap.begin(); it--)
	{
		IScene* scene = (*it).second;

		if (scene != nullptr) 
		{
			delete scene;
			scene = nullptr;
		}
	}

	m_SceneMap.clear();

	// current scene
	if(m_CurrentScene != nullptr)
	{
		delete m_CurrentScene;
		m_CurrentScene = nullptr;
	}
}

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
	for (auto it = m_EntityInWorld.end(); it != m_EntityInWorld.begin();it--)
	{
		StelEntity* entFinded = (*it);

		if (entFinded->GetName() == ent->GetName()) 
		{
			entFinded->Destroy();
			delete entFinded;
			m_EntityInWorld.erase(it);
			break;
		}
	}

	m_EntityMap.erase(ent->GetName());
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
		for (StelEntity* entity : m_EntityInWorld) {
			if (entity != nullptr){
				entity->Destroy();
				delete entity;
			}
		}
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
	for (StelEntity* entity : m_EntityInWorld)
	{
		if (entity != nullptr) entity->Update(dt);
	}
}

void StelWorldService::Draw()
{
	for (StelEntity* entity : m_EntityInWorld)
	{
		if (entity != nullptr) entity->Draw();
	}
}
