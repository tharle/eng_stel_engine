#pragma once
#include "IInput.h"
#include "SDL.h"
#include <map>

class SdlInput : public IInput
{
    public:
        SdlInput();
    private:
        std::map<StelKey, SDL_Scancode> m_InputMap;
        SDL_FPoint m_Axios;
        void InitInputMap();
        void UpdateAxios(float dt);
    protected:
        virtual void Update(float dt) override;
    public:
        virtual bool IsKeyDown(StelKey key) override;
        virtual float GetAxiosHorizontal() override;
        virtual float GetAxiosVertical() override;
};