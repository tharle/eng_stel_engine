#pragma once
#include "IInput.h"
#include "IEvents.h"
#include "IGfx.h"
#include "SDL.h" // Je n'ai pas réussi de faire un foward declaration pour ça
#include <map>

class SdlInput : public IInput
{
    public:
        SdlInput();
        virtual ~SdlInput();
    private:
        std::map<StelKey, SDL_Scancode> m_InputMap;
        StelPointF m_Axios;
        void InitInputMap();
        void UpdateAxios(float dt);
    protected:
        virtual void Update(float dt) override;
    public:
        virtual bool IsKeyDown(StelKey key) override;
        virtual float GetAxiosHorizontal() override;
        virtual float GetAxiosVertical() override;
};