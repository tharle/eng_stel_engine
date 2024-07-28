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
		for (StelObserver<T>* o : m_Observers)
		{
			o->OnNotify(value);
		}
	}
private:
	std::list<StelObserver<T>*> m_Observers;
};