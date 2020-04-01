#pragma once

struct RefCounter {
	RefCounter(long i_StrongRefCount, long i_WeakRefCount) : StrongRefCount(i_StrongRefCount), WeakRefCount(i_WeakRefCount) {}

	long StrongRefCount;
	long WeakRefCount;
};

template<typename T>
class StrongPtr
{
public:
	explicit StrongPtr(T* i_ptr = nullptr) : m_ptr(i_ptr), m_pRefCounter(new RefCounter(1, 0)){}

	~StrongPtr();

	StrongPtr(const StrongPtr<T>& i_other);

	StrongPtr(StrongPtr<T>&& i_other);
	
	StrongPtr& operator=(const StrongPtr<T>& i_other);

	StrongPtr& operator=(StrongPtr<T>&& i_other);

	template<typename T>
	friend class WeakPtr;

	void operator=(std::nullptr_t i_nullptr);

	inline T* operator->() const;
	inline T& operator*() const;
	inline T& Acquire() const;
	inline operator bool() const;
	template<typename U>
	inline bool operator==(const StrongPtr<U>& i_other) const;

private:
	inline void Release();
	RefCounter* m_pRefCounter;
	T* m_ptr;
};

template<typename T>
class WeakPtr
{
public:
	explicit WeakPtr(T* i_ptr = nullptr) : m_ptr(nullptr), m_pRefCounter(new RefCounter(0, 1)){}

	WeakPtr(const StrongPtr<T>& i_other);

	~WeakPtr();

	WeakPtr(const WeakPtr<T>& i_other);

	WeakPtr(WeakPtr<T>&& i_other);

	WeakPtr& operator=(const StrongPtr<T>& i_other);

	WeakPtr& operator=(const WeakPtr<T>& i_other);

	WeakPtr& operator=(WeakPtr<T>&& i_other);
	template <typename U>
	WeakPtr<U>& Cast() {
		return *(reinterpret_cast<WeakPtr<U>*>(this));
	}

	template<typename T>
	friend class StrongPtr;

	void operator=(std::nullptr_t i_nullptr);

	inline T* operator->() const;
	inline T& operator*() const;
	inline operator bool() const;
	inline bool IsValid() const;
	template<typename U>
	inline bool operator==(const WeakPtr<U>& i_other) const;
	

private:
	inline void Release();
	RefCounter* m_pRefCounter;
	T* m_ptr;
};

#include "SmartPtr-inl.h"
#include "SmartPtr-tmpl.h"