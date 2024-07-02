#pragma once
#include "IWorld.h"
#include "IScene.h"
#include "StelEntity.h"
#include <vector>
#include <map>

class StelWorldService : public IWorld
{
    public:
        virtual StelEntity* Create(const char* name) override;
        virtual StelEntity* Find(const char* name) override;
        virtual void Remove(StelEntity* ent) override;

        virtual void LoadScene(const char* sceneName);
        virtual void UnLoad();
        virtual void Register(const char* name, IScene* scene);


        virtual void Update(float dt) override;
        virtual void Draw() override;
    private:
        std::map<const char*, StelEntity*> m_EntityMap = std::map<const char*, StelEntity*>();
        std::vector<StelEntity*> m_EntityInWorld = std::vector<StelEntity*>();
        
        std::map<const char*, IScene*> m_SceneMap = std::map<const char*, IScene*>();
        // current scene
        IScene* m_CurrentScene = nullptr;

};