#pragma once

class Entity
{
	public:
		virtual ~Entity() = default;
		virtual void Start() {}
		virtual void Update(float dt) {}
		virtual void Drawn() {}
		virtual void Destroy() {}
	private:
		const char* m_Name = "";
	public:	
		const char* GetName();
};