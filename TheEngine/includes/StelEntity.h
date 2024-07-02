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
		void Update(float dt);
		void Draw();
	private:
		const char* m_Name = "";
		std::vector<IDrawable*> m_Drawables;
		std::vector<IUpdatable*> m_Updatables;
		std::map<const type_info*, StelComponent*> m_Components;
	public:	
		const char* GetName();


		template<typename T>
		inline T* AddComponent()
		{
			T* comp = new T(this);
			const type_info* type = &typeid(*comp); // _comp
			m_Components.emplace(type, comp); // cmp

			IUpdatable* updable = dynamic_cast<IUpdatable*>(comp);
			if (updable != nullptr) m_Updatables.push_back(updable);

			IDrawable* drawable = dynamic_cast<IDrawable*>(comp);
			if (drawable != nullptr) m_Drawables.push_back(drawable);

			return comp;
		}

		template<typename T>
		T* GetComponent()
		{
			T temp;
			const type_info* type = &typeid(*temp); // _comp
			return m_Components.at(type_info);
		}
};
