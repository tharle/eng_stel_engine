#pragma once
#include <vector>
#include <map>
#include "IDrawable.h"
#include "IUpdatable.h"

class StelComponent;

class StelEntity final : public IDrawable, public IUpdatable
{
	public:
		StelEntity();
		StelEntity(const char* name);
		template<typename T> void AddComponent(T* comp);
		template<typename T> T* GetComponent();
		void Update(float dt);
		void Draw();
	private:
		const char* m_Name = "";
		std::vector<IDrawable*> m_Drawables;
		std::vector<IUpdatable*> m_Updatables;
		std::map<const type_info*, StelComponent*> m_Components;
	public:	
		const char* GetName();
};
