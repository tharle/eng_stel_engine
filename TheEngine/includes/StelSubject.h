#pragma once
#include "StelObserver.h"
#include <list>

template<typename T>
class StelSubject
{
public:
	void AddListener(StelObserver<T>* o)
	{
		m_Observers.push_back(o);
	}

	void RemoveListener(StelObserver<T>* o)
	{
		m_Observers.remove(o);
	}

	void Invoke(const T& value)
	{
		if (m_Observers.size() <= 0) return;

		for (StelObserver<T>* o : m_Observers)
		{
			if(o->IsActive()) o->OnNotify(value);
		}
	}

	void Clear() 
	{
		m_Observers.clear();
	}
private:
	std::list<StelObserver<T>*> m_Observers;
};
