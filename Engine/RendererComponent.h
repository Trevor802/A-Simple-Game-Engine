#pragma once
#include "BaseComponent.h"
#include "GLib.h"
class RendererComponent : public BaseComponent
{
public:
	RendererComponent(GameObject* i_pGameObject) : BaseComponent(i_pGameObject) {};
	void Update(float DeltaTime) override;
	inline void SetSprite(GLib::Sprites::Sprite* const i_pSprite) { m_pSprite = i_pSprite; }

private:
	GLib::Sprites::Sprite* m_pSprite;
};

