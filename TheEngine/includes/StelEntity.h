#pragma once
#include <vector>
#include <map>
#include <string>
#include "IGfx.h"
#include "IDrawable.h"
#include "IUpdatable.h"

class StelComponent;

struct StelTransform {
	StelPointF Position;
	StelPointF Dimension;
	float Angle;

	inline StelTransform(StelRectF rect, float angle) : 
		Position({ rect.x, rect.y }),
		Dimension({ rect.w, rect.h }),
		Angle(angle)
	{}

	inline StelTransform(StelRectF rect) : StelTransform(rect, 0.0f){}

	inline StelRectF GetRect() 
	{
		return { Position.x, Position.y, Dimension.x, Dimension.y };
	}
};

class StelEntity final : public IDrawable, public IUpdatable
{
	public:
		StelEntity();
		StelEntity(std::string name);
		StelEntity(std::string name, StelRectF rect);
		virtual ~StelEntity() = default;
		void Update(float dt);
		void Draw();
		void Destroy();
	private:
		StelTransform m_Transform;
		std::string m_Name = "";
		std::vector<IDrawable*> m_Drawables = std::vector<IDrawable*>();
		std::vector<IUpdatable*> m_Updatables = std::vector<IUpdatable*>();
		std::map<const type_info*, StelComponent*> m_Components = std::map<const type_info*, StelComponent*>();
	public:	
		std::string GetName();
		StelTransform GetTransform();

		template<typename T>
		inline T* AddComponent()
		{
			T* comp = new T(this);
			const type_info* type = &typeid(*comp); // _comp
			m_Components.emplace(type, comp); // cmp
			 // reinterpret_cast
			IUpdatable* updable = dynamic_cast<IUpdatable*>(comp);
			if (updable != nullptr) m_Updatables.push_back(updable);

			IDrawable* drawable = dynamic_cast<IDrawable*>(comp);
			if (drawable != nullptr) m_Drawables.push_back(drawable);

			return comp;
		}

		template<typename T>
		T* GetComponent()
		{
			T temp(this);
			const type_info* type = &typeid(temp); // _comp

			if (m_Components.count(type) == 0) return nullptr;

			return (T*)m_Components.at(type);
		}
};
