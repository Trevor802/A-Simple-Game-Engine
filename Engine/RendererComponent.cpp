#include "RendererComponent.h"
#include "GameObject.hpp"

void RendererComponent::Update(float DeltaTime) {
	GLib::Sprites::RenderSprite(*m_pSprite, gameObject->GetPosition().ToPoint2D(), gameObject->GetRotRad());
}

