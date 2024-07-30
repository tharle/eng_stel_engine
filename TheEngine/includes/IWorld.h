#pragma once
#include "StelEntity.h"
#include "IScene.h"
#include <string>

class IWorld 
{
    public:
        virtual ~IWorld() = default;
        // -----------------------------
        // ENTITY
        // -----------------------------
        virtual StelEntity* Create(std::string name) = 0;
        virtual StelEntity* CreateLater(std::string name) = 0;
        virtual StelEntity* Find(std::string  name) = 0;
        virtual void Remove(StelEntity* ent) = 0;
        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;

        // -----------------------------
        // SCENE
        // -----------------------------
        virtual void Add(StelEntity* entity) = 0;
        virtual void LoadScene(std::string  sceneName) = 0;
        virtual void UnLoad() = 0;
        virtual void Register(std::string  name, IScene* scene) = 0;


        // -----------------------------
        // GAME
        // -----------------------------
        virtual void ExitGame() = 0;
};