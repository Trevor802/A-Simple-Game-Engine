#pragma once
#include "SmartPtr.h"

template<typename T>
StrongPtr<T>::~StrongPtr() {
	Release();
}