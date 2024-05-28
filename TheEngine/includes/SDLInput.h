#pragma once
#include "IInput.h"


class SdlInput : public IInput
{
    protected:
        virtual void Update() override;
    public:
        virtual int IsKeyDown(int key) override;
};