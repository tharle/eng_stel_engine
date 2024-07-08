#include <SdlAudio.h>
#include <SDL_mixer.h>

SdlAudio::SdlAudio()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
}

SdlAudio::~SdlAudio()
{
    Mix_CloseAudio();

    for (auto cmp : m_SoundCache)
    {
        if (cmp.second != nullptr) SDL_free(cmp.second);
    }

    for (auto cmp : m_MusicCache)
    {
        if (cmp.second != nullptr) SDL_free(cmp.second);
    }

    m_SoundCache.clear();
    m_MusicCache.clear();

}

size_t SdlAudio::LoadMusic(const std::string& filename)
{
    const size_t _musId = std::hash<std::string>()(filename);
    if (m_MusicCache.count(_musId) > 0)
    {
        return _musId;
    }

    Mix_Music* _mus = Mix_LoadMUS(filename.c_str());
    if (_mus)
    {
        m_MusicCache.emplace(_musId, _mus);
        return _musId;
    }

    //homer::Engine::Get().Logger().LogMessage("Error with music: " + filename);
    //homer::Engine::Get().Logger().LogMessage(Mix_GetError());

    return 0;
}

size_t SdlAudio::LoadSound(const std::string& filename)
{
    const size_t _sfxId = std::hash<std::string>()(filename);
    if (m_SoundCache.count(_sfxId) > 0)
    {
        return _sfxId;
    }

    Mix_Chunk* _sfx = Mix_LoadWAV(filename.c_str());
    if (_sfx)
    {
        m_SoundCache.emplace(_sfxId, _sfx);
        return _sfxId;
    }

    //homer::Engine::Get().Logger().LogMessage("Error with sfx: " + filename);
    //homer::Engine::Get().Logger().LogMessage(Mix_GetError());
    return 0;
}

void SdlAudio::PlayMusic(size_t id)
{
    PlayMusic(id, -1);
}

void SdlAudio::PlayMusic(size_t id, int loop)
{
    Mix_PlayMusic(m_MusicCache[id], loop);
}

void SdlAudio::PlaySFX(size_t id)
{
    PlaySFX(id, 0);
}

void SdlAudio::PlaySFX(size_t id, int loop)
{
    Mix_PlayChannel(-1, m_SoundCache[id], loop);
}

void SdlAudio::PauseMusic()
{
    Mix_PauseMusic();
}

void SdlAudio::StopMusic()
{
    Mix_HaltMusic();
}

void SdlAudio::ResumeMusic()
{
    Mix_ResumeMusic();
}

void SdlAudio::SetVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

void SdlAudio::SetVolume(size_t soundId, int volume)
{
    Mix_VolumeChunk(m_SoundCache[soundId], volume);
}