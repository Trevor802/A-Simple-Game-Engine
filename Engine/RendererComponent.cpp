#include "RendererComponent.h"
#include "GameObject.hpp"

void RendererComponent::Update() {
	GLib::Sprites::RenderSprite(*m_pSprite, gameObject->GetPosition().ToPoint2D(), 0.0f);
}