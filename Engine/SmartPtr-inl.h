#pragma once
#include "SmartPtr.h"
#include <assert.h>

#pragma region StrongPtr
template<typename T>
inline StrongPtr<T>::operator bool() const { return m_ptr != nullptr; }


template<typename T>
template<typename U>
inline bool StrongPtr<T>::operator==(const StrongPtr<U>& i_other) const { return m_ptr == i_other.m_ptr; }

template<typename T>
inline T* StrongPtr<T>::operator->() { return m_ptr; }

template<typename T>
inline T& StrongPtr<T>::operator*() {
	assert(m_ptr != nullptr);
	return *m_ptr;
}

template<typename T>
inline void StrongPtr<T>::Release() {
	assert(m_pRefCounter->StrongRefCount > 0);
	if (--(m_pRefCounter->StrongRefCount) == 0) {
		delete m_ptr;
		if (m_pRefCounter->WeakRefCount == 0)
			delete m_pRefCounter;
	}
}
#pragma endregion

#pragma region WeakPtr
template<typename T>
inline WeakPtr<T>::operator bool() const { return IsValid(); }

template<typename T>
template<typename U>
inline bool WeakPtr<T>::operator==(const WeakPtr<U>& i_other) const { return m_ptr == i_other.m_ptr; }

template<typename T>
inline bool WeakPtr<T>::IsValid() const {
	return m_ptr != nullptr;
}

template<typename T>
inline T* WeakPtr<T>::operator->() { return m_ptr; }

template<typename T>
inline T& WeakPtr<T>::operator*() {
	assert(m_ptr != nullptr);
	return *m_ptr;
}

template<typename T>
inline void WeakPtr<T>::Release() {
	if (!m_pRefCounter) return;
	assert(m_pRefCounter->WeakRefCount > 0);
	m_pRefCounter->WeakRefCount--;
}
#pragma endregion
