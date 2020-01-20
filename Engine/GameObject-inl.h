#include "GameObject.hpp"
#pragma once

template <typename T>
inline T* GameObject::AddComponent(T* i_pComponent) {
	dynamic_cast<BaseComponent*>(i_pComponent)->gameObject = this;
	m_Components.emplace_back(i_pComponent);
	return i_pComponent;
}
