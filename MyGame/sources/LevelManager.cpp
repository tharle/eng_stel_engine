#include "LevelManager.h"




void LevelManager::Start()
{
	m_Background = StelTileMap(m_EntityParent);
	m_Background.Load("Assets/adv_lolo_map.png", { 16, 16 }, { 16, 16 }, 2);
	TLayer nLayer = {
		{ -1,4,6,6,6,5,5,6,6,5,5,6,6,7,-1,-1},
        {-1,40,41,42,42,42,42,42,148,42,42,42, 42,43,-1,-1},
        {-1,40,36,37,37,37,37,37,1,37,37,73,73,79,-1,-1},
        {-1,40,36,73,73,37,109,1,1,37,37,73,73,79,-1,-1},
        {-1,40,0,73,73,37,37,37,1,37,37,37,73,79,-1,-1},
        {-1,40,0,1,73,73,37,37,1,37,37,37,73,79,-1,-1},
        {-1,40,0,1,1,1,37,37,1,37,37,73,109,79,-1,-1},
        {-1,40,0,1,1,1,1,1,1,1,37,1,1,79,-1,-1},
        {-1,40,0,1,1,1,1,1,1,1,1,1,1,79,-1,-1},
        {-1,40,0,73,73,1,1,1,1,73,73,1,1,79,-1,-1},
        {-1,40,72,73,73,73,1,1,1,73,73,73,1,79,-1,-1},
        {-1,40,72,73,73,73,1,1,1,1,73,73,1,79,-1,-1},
        {-1,76,36,73,73,37,110,1,1,1,1,1,1,79,-1,-1},
        {-1,76,36,37,37,37,37,37,1,1,1,1,1,79,-1,-1},
        {-1,112,113,114,114,113,114,113,113,113,113,113,113,115,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	};
	m_Background.AddLayer("level_1_map", nLayer, false);

    TLayer colliderLayer = {
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,200,-1,200,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,200,200,200,-1,200,-1,-1,-1,-1,-1,-1},
        {-1,200,200,200,-1,200,-1,-1,-1,200,-1,-1,-1,200,-1,-1},
        {-1,200,-1,200,200,200,200,200,-1,200,-1,-1,-1,200,-1,-1},
        {-1,200,-1,-1,200,200,200,200,-1,200,-1,200,200,200,-1,-1},
        {-1,200,-1,-1,-1,-1,200,200,-1,200,200,200,-1,200,-1,-1},
        {-1,200,-1,-1,-1,-1,-1,-1,-1,-1,200,-1,-1,200,-1,-1},
        {-1,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,200,-1,-1},
        {-1,200,-1,200,200,-1,-1,-1,-1,200,200,-1,-1,200,-1,-1},
        {-1,200,200,200,200,200,-1,-1,-1,200,200,200,-1,200,-1,-1},
        {-1,-1,-1,-1,-1,200,-1,-1,-1,-1,200,200,-1,200,-1,-1},
        {-1,-1,-1,-1,-1,200,-1,-1,-1,-1,-1,-1,-1,200,-1,-1},
        {-1,-1,-1,-1,-1,200,200,200,-1,-1,-1,-1,-1,200,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,200,200,200,200,200,200,200,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
    };
    m_Background.AddLayer("level_1_collider", colliderLayer, true);
    m_Background.DrawColliders = true;

    // Load sounds and audios
    m_AmbianceMusic = Audio().LoadMusic("Assets/Audios/bgm.wav");
    if (m_AmbianceMusic == 0)  Log().Print(LOG_WARNING, "ERROR LOAD MUSIC");
    //Audio().PlayMusic(m_AmbianceMusic);
}

void LevelManager::Update(float dt)
{
    ChangeScene(dt);
}

void LevelManager::ChangeScene(float dt)
{
    if (m_CooldownChangeScene > 0) m_CooldownChangeScene -= dt;
    if (Input().IsKeyDown(IInput::Space) && m_CooldownChangeScene <= 0)
    {
        World().LoadScene("MainMenu");

        Log().Print(LOG_INFO, "SPACE WAS PRESSED");
        m_CooldownChangeScene = COOLDOWN_CHANGE_SCENE;
    }
}

void LevelManager::Draw()
{
	m_Background.Draw();
}

bool LevelManager::IsColliding(StelRectF boxCollider)
{
    int tileIndex;
    return m_Background.IsColliding(boxCollider, &tileIndex);
}
