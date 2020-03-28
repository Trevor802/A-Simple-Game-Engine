#pragma once

template<typename T>
StrongPtr<T> GameObject::GetComponent()
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if (dynamic_cast<const T*>((*it).operator->())) {
			return *(reinterpret_cast<StrongPtr<T>*>(&(*it)));
		}
	}
	return StrongPtr<T>();
}