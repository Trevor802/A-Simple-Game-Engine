#include "GameObject.hpp"
#pragma once

template <typename T>
inline StrongPtr<T> GameObject::AddComponent(StrongPtr<T>& i_pComponent) {
	(dynamic_cast<BaseComponent*>(i_pComponent.operator->()))->gameObject = self;
	StrongPtr<BaseComponent> base = *(reinterpret_cast<StrongPtr<BaseComponent>*>(&i_pComponent));
	m_Components.emplace_back(base);
	return i_pComponent;
};
