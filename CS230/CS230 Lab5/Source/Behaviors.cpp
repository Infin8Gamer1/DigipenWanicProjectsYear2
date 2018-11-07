#include "stdafx.h"
#include "Behaviors.h"
#include "Transform.h"
#include "Physics.h"
#include <Input.h>
#include <Graphics.h>

void Behaviors::UpdateShip(Transform * transform, Physics * physics)
{
	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	Vector2D force = MousePos - transform->GetTranslation();

	physics->AddForce(force.Normalized() * 5000.0f);

	physics->SetAngularVelocity(10.0f);
}
