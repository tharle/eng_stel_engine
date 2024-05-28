#pragma once
#include "IInput.h"


class SDLInput : public IInput
{
    protected:
        virtual void Update() override;
    public:
        virtual int IsKeyDown(int key) override;
};