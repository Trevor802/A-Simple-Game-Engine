#include "RendererComponent.h"
#include "GameObject.hpp"

void RendererComponent::Update(float DeltaTime) {
	GLib::Sprites::RenderSprite(*m_pSprite, gameObject->transform->GetPosition().ToPoint2D(), 
		gameObject->transform->GetRotRad());
}

