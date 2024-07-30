#pragma once
#include "IWorld.h"
#include "IScene.h"
#include "StelEntity.h"
#include <vector>
#include <map>


class StelWorld : public IWorld
{
    public:
        virtual ~StelWorld();
        virtual StelEntity* Create(std::string name) override;
        virtual StelEntity* CreateLater(std::string name) override;
        virtual StelEntity* Find(std::string name) override;
        virtual void Remove(StelEntity* ent) override;

        virtual void LoadScene(std::string sceneName);
        virtual void UnLoad();
        virtual void Register(std::string name, IScene* scene);
        virtual void Add(StelEntity* entity) override;
        virtual void ExitGame();


        virtual void Update(float dt) override;
        virtual void Draw() override;
    private:
        std::map<std::string, StelEntity*> m_EntityMap = std::map<std::string, StelEntity*>();
        std::vector<StelEntity*> m_EntityInWorld = std::vector<StelEntity*>();
        std::vector<StelEntity*> m_EntitiesToBeCreateInNextFrame = std::vector<StelEntity*>();
        
        std::map<std::string, IScene*> m_SceneMap = std::map<std::string, IScene*>();
        // current scene
        IScene* m_CurrentScene = nullptr;
        std::string m_NextSceneToLoad = "";

        void CheckAndLoadScene();
        void AddAllLateEnityToWorld();
};