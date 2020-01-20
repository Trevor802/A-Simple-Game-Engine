#pragma once

template<typename T>
T* GameObject::GetComponent()
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if (dynamic_cast<const T*>(it->get())) {
			return dynamic_cast<T*>(it->get());
		}
	}
	return NULL;
}