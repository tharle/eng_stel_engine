#pragma once
#include <vector>

class IInput
{
    //protected:
public:
    static enum Key
    {
        None,
        Right, Up, Left, Down,
        Esc,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z

    };

    virtual void Update(float dt) = 0;
    virtual bool IsKeyDown(Key key) = 0;
    virtual float GetAxiosHorizontal() = 0;
    virtual float GetAxiosVertical() = 0;

    // TODO Add mapping for vertical and horizontal axios

    friend class Engine;
};