#pragma once

template <typename T>
inline T* GameObject::AddComponent(T* i_pComponent) {
	m_Components.emplace_back(i_pComponent);
	return i_pComponent;
}