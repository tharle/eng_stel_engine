#include "StelWorldService.h"
#include "StelEngine.h"

StelWorldService::~StelWorldService()
{
	UnLoad();
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

void StelWorldService::Update(float dt)
{
	for (StelEntity* entity : m_EntityInWorld)
	{
		if (entity != nullptr) entity->Update(dt);
	}

	CheckAndLoadScene();
}

void StelWorldService::Draw()
{
	for (StelEntity* entity : m_EntityInWorld)
	{
		if (entity != nullptr) entity->Draw();
	}
}

StelEntity* StelWorldService::Find(std::string name)
{
	return m_EntityMap.at(name);
}

void StelWorldService::Remove(StelEntity* ent)
{
	for (auto it = m_EntityInWorld.end()-1; it != m_EntityInWorld.begin()-1;it--)
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
	m_NextSceneToLoad = sceneName;
}

void StelWorldService::CheckAndLoadScene()
{
	if (m_SceneMap.count(m_NextSceneToLoad) > 0)
	{
		UnLoad();
		m_CurrentScene = m_SceneMap[m_NextSceneToLoad];
		m_CurrentScene->Load();
		m_NextSceneToLoad = "";
	}
	else if (m_NextSceneToLoad.size() != 0) 
	{
		std::string msg = "StelWorld: Load Scene fail at " + m_NextSceneToLoad;
		Stel::Engine::Get().GetLoggerService().Print(LOG_ERROR, msg.c_str());
		m_NextSceneToLoad = "";
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
