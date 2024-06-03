#pragma once
#include "IInput.h"
#include <map>
#include "SDL.h"

class SdlInput : public IInput
{
    public:
        SdlInput();
    private:
        std::map<Key, SDL_Scancode> m_InputMap;
        void InitInputMap();
    protected:
        virtual void Update() override;
    public:
        virtual bool IsKeyDown(Key key) override;
        virtual float GetAxiosHorizontal() override;
        virtual float GetAxiosVertical() override;
};