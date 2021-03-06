#pragma once
#include "SmartPtr.h"

#pragma region StrongPtr
template<typename T>
StrongPtr<T>::~StrongPtr() {
	Release();
}

template<typename T>
StrongPtr<T>& StrongPtr<T>::operator=(const StrongPtr<T>& i_other) {
	if (&i_other == this)
		return *this;
	m_pRefCounter = i_other.m_pRefCounter;
	m_ptr = i_other.m_ptr;
	m_pRefCounter->StrongRefCount++;
	return *this;
}

template<typename T>
StrongPtr<T>::StrongPtr(const StrongPtr<T>& i_other) : m_ptr(i_other.m_ptr), m_pRefCounter(i_other.m_pRefCounter) {
	m_pRefCounter->StrongRefCount++;
}

template<typename T>
StrongPtr<T>& StrongPtr<T>::operator=(StrongPtr<T>&& i_other) {
	if (&i_other == this)
		return *this;
	m_pRefCounter = i_other.m_pRefCounter;
	m_ptr = i_other.m_ptr;
	i_other.m_pRefCounter = nullptr;
	i_other.m_ptr = nullptr;
	return *this;
}


template<typename T>
StrongPtr<T>::StrongPtr(StrongPtr<T>&& i_other) : m_ptr(i_other.m_ptr), m_pRefCounter(i_other.m_pRefCounter)
{
	i_other.m_ptr = nullptr;
	i_other.m_pRefCounter = nullptr;
}

template<typename T>
void StrongPtr<T>::operator=(std::nullptr_t i_nullptr) {
	Release();
}
#pragma endregion

#pragma region WeakPtr
template<typename T>
WeakPtr<T>::~WeakPtr() {
	Release();
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& i_other) {
	if (&i_other == this)
		return *this;
	m_pRefCounter = i_other.m_pRefCounter;
	m_ptr = i_other.m_ptr;
	m_pRefCounter->WeakRefCount++;
	return *this;
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const StrongPtr<T>& i_other) {
	if (i_other.m_ptr == m_ptr)
		return *this;
	m_pRefCounter = i_other.m_pRefCounter;
	m_ptr = i_other.m_ptr;
	m_pRefCounter->WeakRefCount++;
	return *this;
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& i_other) {
	if (&i_other == this)
		return *this;
	m_pRefCounter = i_other.m_pRefCounter;
	m_ptr = i_other.m_ptr;
	i_other.m_pRefCounter = nullptr;
	i_other.m_ptr = nullptr;
	return *this;
}

template<typename T>
WeakPtr<T>::WeakPtr(const StrongPtr<T>& i_other) : m_ptr(i_other.m_ptr), m_pRefCounter(i_other.m_pRefCounter) {
	m_pRefCounter->WeakRefCount++;
}

template<typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& i_other) : m_ptr(i_other.m_ptr), m_pRefCounter(i_other.m_pRefCounter) {
	m_pRefCounter->WeakRefCount++;
}

template<typename T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& i_other) : m_ptr(i_other.m_ptr), m_pRefCounter(i_other.m_pRefCounter)
{
	i_other.m_ptr = nullptr;
	i_other.m_pRefCounter = nullptr;
}

template<typename T>
void WeakPtr<T>::operator=(std::nullptr_t i_nullptr) {
	Release();
}

#pragma endregion
