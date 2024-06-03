 #include "SdlInput.h"

SdlInput::SdlInput()
{
    InitInputMap();
}

void SdlInput::InitInputMap() 
{
    m_InputMap = std::map<Key, SDL_Scancode>();
    m_InputMap[Right] = SDL_SCANCODE_RIGHT;
    m_InputMap[Up] = SDL_SCANCODE_UP;
    m_InputMap[Left] = SDL_SCANCODE_LEFT;
    m_InputMap[Down] = SDL_SCANCODE_DOWN;


    m_InputMap[A] = SDL_SCANCODE_A;
    m_InputMap[B] = SDL_SCANCODE_B;
    m_InputMap[C] = SDL_SCANCODE_C;
    m_InputMap[D] = SDL_SCANCODE_D;
    m_InputMap[E] = SDL_SCANCODE_E;
    m_InputMap[F] = SDL_SCANCODE_F;
    m_InputMap[G] = SDL_SCANCODE_G;
    m_InputMap[H] = SDL_SCANCODE_H;
    m_InputMap[I] = SDL_SCANCODE_I;
    m_InputMap[J] = SDL_SCANCODE_J;
    m_InputMap[K] = SDL_SCANCODE_K;
    m_InputMap[L] = SDL_SCANCODE_L;
    m_InputMap[M] = SDL_SCANCODE_M;
    m_InputMap[N] = SDL_SCANCODE_N;
    m_InputMap[O] = SDL_SCANCODE_O;
    m_InputMap[P] = SDL_SCANCODE_P;
    m_InputMap[Q] = SDL_SCANCODE_Q;
    m_InputMap[R] = SDL_SCANCODE_R;
    m_InputMap[S] = SDL_SCANCODE_S;
    m_InputMap[T] = SDL_SCANCODE_T;
    m_InputMap[U] = SDL_SCANCODE_U;
    m_InputMap[V] = SDL_SCANCODE_V;
    m_InputMap[X] = SDL_SCANCODE_X;
    m_InputMap[W] = SDL_SCANCODE_W;
    m_InputMap[Y] = SDL_SCANCODE_Y;
    m_InputMap[Z] = SDL_SCANCODE_Z;

}
 
bool SdlInput::IsKeyDown(Key key)
{
    if  (m_InputMap.find(key) == m_InputMap.end()) return false;

    SDL_Scancode sdlKey = m_InputMap[key];

    const unsigned char* _keyStates = SDL_GetKeyboardState(nullptr);
    return _keyStates[sdlKey];
}

float SdlInput::GetAxiosHorizontal()
{
    float axios = 0.0f;

    if (IsKeyDown(A) || IsKeyDown(Left)) axios = -1;
    else if (IsKeyDown(D) || IsKeyDown(Right)) axios = 1;

    return axios;
}

float SdlInput::GetAxiosVertical()
{
    float axios = 0.0f;

    if (IsKeyDown(S) || IsKeyDown(Down)) axios = 1;
    else if (IsKeyDown(W) || IsKeyDown(Up)) axios = -1;

    return axios;
}

void SdlInput::Update()
{

}