#pragma once

template<typename T>
class StelObserver {
public:
	virtual ~StelObserver() = default;
	virtual void OnNotify(const T& value) = 0;
	virtual bool IsActive() { return true; }
};