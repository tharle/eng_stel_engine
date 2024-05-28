#pragma once
class IInput 
{
    //protected:
    public:
        virtual void Update() = 0;
        virtual int IsKeyDown(int key) = 0;

        friend class Engine;
};