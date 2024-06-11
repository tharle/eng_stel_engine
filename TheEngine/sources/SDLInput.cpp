 #include "SdlInput.h"

SdlInput::SdlInput() : m_Axios({0, 0})
{
    InitInputMap();
}

SdlInput::~SdlInput()
{
    m_InputMap.clear();
}

void SdlInput::InitInputMap() 
{
    m_InputMap = std::map<StelKey, SDL_Scancode>();
    m_InputMap[Right] = SDL_SCANCODE_RIGHT;
    m_InputMap[Up] = SDL_SCANCODE_UP;
    m_InputMap[Left] = SDL_SCANCODE_LEFT;
    m_InputMap[Down] = SDL_SCANCODE_DOWN;
    m_InputMap[Esc] = SDL_SCANCODE_ESCAPE;


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
 
bool SdlInput::IsKeyDown(StelKey key)
{
    if  (m_InputMap.find(key) == m_InputMap.end()) return false;

    SDL_Scancode sdlKey = m_InputMap[key];

    const unsigned char* _keyStates = SDL_GetKeyboardState(nullptr);
    return _keyStates[sdlKey];
}

float SdlInput::GetAxiosHorizontal()
{
    return m_Axios.x;
}

float SdlInput::GetAxiosVertical()
{
    float axios = 0.0f;

    if (IsKeyDown(S) || IsKeyDown(Down)) axios = 1;
    else if (IsKeyDown(W) || IsKeyDown(Up)) axios = -1;


    return m_Axios.y;
}

void SdlInput::Update(float dt)
{
    UpdateAxios(dt);
}

void SdlInput::UpdateAxios(float dt)
{

    // TODO change when have controls inputs saves in engine
    if (IsKeyDown(A) || IsKeyDown(Left))
    {
        m_Axios.x = m_Axios.x < 0 ? m_Axios.x : 0;
        m_Axios.x -= dt;

        m_Axios.x = m_Axios.x > -1 ? m_Axios.x : -1;
    }
    else if (IsKeyDown(D) || IsKeyDown(Right))
    {
        m_Axios.x = m_Axios.x > 0 ? m_Axios.x : 0;
        m_Axios.x += dt;
        m_Axios.x = m_Axios.x < 1 ? m_Axios.x : 1;
    }
    else {
        m_Axios.x = 0;
    }

    if (IsKeyDown(S) || IsKeyDown(Down))
    {
        m_Axios.y = m_Axios.y > 0 ? m_Axios.y : 0;
        m_Axios.y += dt;
        m_Axios.y = m_Axios.y < 1 ? m_Axios.y : 1;
    }
    else if (IsKeyDown(W) || IsKeyDown(Up))
    {
        m_Axios.y = m_Axios.y < 0 ? m_Axios.y : 0;
        m_Axios.y -= dt;
        m_Axios.y = m_Axios.y > -1 ? m_Axios.y : -1;
    }
    else {
        m_Axios.y = 0;
    }
}