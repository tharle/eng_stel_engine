#pragma once
#include "Entity.h"
#include "IScene.h"

class IWorld 
{
    public:
        // -----------------------------
        // ENTITY
        // -----------------------------
        virtual void Add(Entity* ent) = 0;
        virtual Entity* Find(const char* name) = 0;
        virtual void Remove(Entity* ent) = 0;

        // -----------------------------
        // SCENE
        // -----------------------------
        virtual void LoadScene(const char* sceneName) = 0;
        virtual void Register(const char* name, IScene* scene) = 0;
};