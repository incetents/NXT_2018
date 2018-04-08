#include "stdafx.h"

#include "OBB.h"
#include "../Math/Transform.h"
#include "../Math/Matrix4x4.h"

OBB2D::OBB2D(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
}

Vec2 OBB2D::getPosition() const
{
	if (m_transform == nullptr)
	{
		SimpleLogger.ErrorStatic("Getting Position from null Transform");
		return Vec2();
	}
	Matrix4x4 model = m_transform->getModel();

	return Vec2(model * Vec3());
}

void OBB2D::Update(float delta)
{

}

void OBB2D::Draw(Color3F color) const
{
	if (m_transform != nullptr)
	{
		Matrix4x4 model = m_transform->getModel();

		Vec3 Pos1 = model * Vec3(-0.5f, -0.5f, 0);
		Vec3 Pos2 = model * Vec3(+0.5f, -0.5f, 0);
		Vec3 Pos3 = model * Vec3(+0.5f, +0.5f, 0);
		Vec3 Pos4 = model * Vec3(-0.5f, +0.5f, 0);

		App::DrawLine(Pos1, Pos2, color, color);
		App::DrawLine(Pos2, Pos3, color, color);
		App::DrawLine(Pos3, Pos4, color, color);
		App::DrawLine(Pos4, Pos1, color, color);
	}

}