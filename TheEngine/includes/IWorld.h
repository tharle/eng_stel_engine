#pragma once
#include "StelEntity.h"
#include "IScene.h"

class IWorld 
{
    public:
        // -----------------------------
        // ENTITY
        // -----------------------------
        virtual StelEntity* Create(const char* name) = 0;
        virtual StelEntity* Find(const char* name) = 0;
        virtual void Remove(StelEntity* ent) = 0;
        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;

        // -----------------------------
        // SCENE
        // -----------------------------
        virtual void LoadScene(const char* sceneName) = 0;
        virtual void Register(const char* name, IScene* scene) = 0;
};