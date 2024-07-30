#pragma once
#include <vector>
#define TIMEOUT_KEY_DOWN 0.1f

class IInput
{
    //protected:
public:
    enum StelKey
    {
        None,
        Right, Up, Left, Down,
        Esc, Space, LShift, RShift,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    };

    virtual ~IInput() = default;
    virtual void Update(float dt) = 0;
    virtual bool IsKeyDown(StelKey key) = 0;
    virtual float GetAxiosHorizontal() = 0;
    virtual float GetAxiosVertical() = 0;

    // TODO Add mapping for vertical and horizontal axios

    friend class Engine;
};