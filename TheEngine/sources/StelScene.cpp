#include "StelScene.h"
#include "StelEngine.h"

StelEntity* StelScene::Instantiate(const std::string& name)
{
	return Stel::Engine::Get().GetWorld().Create(name);
}
