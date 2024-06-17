#pragma once
#include <vector>

class StelComponent;

class StelEntity final
{
	public:
		StelEntity();
		StelEntity(const char* name);
		void AddComponent(StelComponent* comp);
		void Update(float dt);
		void Draw();
	private:
		const char* m_Name = "";
		std::vector<StelComponent*> m_Components;
	public:	
		const char* GetName();
};