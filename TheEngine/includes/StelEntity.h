#pragma once
#include <vector>
#include <map>
#include <string>
#include "IGfx.h"
#include "IDrawable.h"
#include "IUpdatable.h"

class StelComponent;

struct StelTransform {
	StelPointF Position{ 0.0f, 0.0f };
	StelPointF Size { 0.0f, 0.0f };
	float Angle = 0.0f;
	float Scale = 1.0f;

	inline StelTransform(StelRectF rect, float scale, float angle) : 
		Position({ rect.x, rect.y }),
		Size({ rect.w, rect.h }),
		Scale(scale),
		Angle(angle)
	{}

	inline StelTransform(StelRectF rect, float scale) : StelTransform(rect, scale ,0.0f){}
	inline StelTransform(StelRectF rect) : StelTransform(rect, 1.0f, 0.0f) {}

	inline StelRectF GetRect() 
	{
		return { Position.x, Position.y, Size.x, Size.y };
	}

	inline StelRectF GetTrueRect() 
	{
		return { Position.x, Position.y, Size.x * Scale, Size.y * Scale };
	}

	inline StelTransform Translate(StelPointF shift) 
	{
		Position.x += shift.x;
		Position.y += shift.y;

		return *(this);
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
		bool m_IsActive = true;
	public:	
		std::string GetName();
		bool IsActive();
		StelTransform GetTransform();
		// { 200.0f, 300.0f }, { 16, 16 }, scaleFactor
		
		inline void SetTransform(StelPointF position, StelPointF size, float scale, float angle)
		{
			SetTransform(StelTransform({ position.x, position.y, size.x, size.y }, scale, angle));
		}

		inline void SetTransform(StelTransform nTransform) {
			m_Transform = nTransform;
		}

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
