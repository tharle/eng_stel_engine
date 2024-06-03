#pragma once
#include "IWorld.h"
#include <vector>
#include <map>

class WorldService : public IWorld
{
    public:
        virtual void Add(Entity* ent) override;
        virtual Entity* Find(const char* name) override;
        virtual void Remove(Entity* ent) override;

        virtual void LoadScene(const char* sceneName);
        virtual void Register(const char* name, IScene* scene);


        void Update(float dt);
        void Draw();
    private:
        std::vector<Entity*> m_Entities = std::vector<Entity*>();
        std::map<const char*, Entity*> m_EntityMap = std::map<const char*, Entity*>();
        // current scene
};