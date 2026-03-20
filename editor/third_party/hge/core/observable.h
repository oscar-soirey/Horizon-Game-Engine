#ifndef HGE_OBSERVABLE_H
#define HGE_OBSERVABLE_H

#include "build_dll.h"

template<typename T>
class ENGINE_API Observable {
public:
	Observable() = default;
	Observable(const T& v) : value(v) {}

	void Set(T value);
	T Get();

private:
	bool dirty = false;
	T value;
};