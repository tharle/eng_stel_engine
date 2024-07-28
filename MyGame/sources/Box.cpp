#include "Box.h"
#include "StelAtlas.h"
#include "PlayerControls.h"
#include "LevelManager.h"


void Box::Start(char* spriteSheet, StelPointI frame, LevelManager* currentLevel)
{
	StelComponent::Start();

	m_CurrentLevel = currentLevel;

	float offset = OFFSET_COLLIDER;
	m_Collider = { -offset,-offset, -offset , -offset };

	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init(spriteSheet);
	StelPointI size = StelPointI::FromFloat(m_EntityParent->GetTransform().Size.x, m_EntityParent->GetTransform().Size.y);
	m_Model->AddFrame({ frame.x * size.x, frame.y * size.y, size.x, size.y });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Box::Update(float dt)
{
	Move(dt);
}


void Box::Move(float dt)
{
	StelEntity* other = Physic().CollideWithLayer(m_EntityParent, LAYER_NAME_PLAYER);
	if (other && other->GetComponent<PlayerControls>())
	{
		float speed = other->GetComponent<PlayerControls>()->GetSpeed();
		float axiosV = Input().GetAxiosVertical();
		float axiosH = axiosV == 0 ? Input().GetAxiosHorizontal() : 0;

		StelPointF diff = GetTransform().Position.Diff(other->GetTransform().Position);


		// Check if player is moving the box in the good direction 
		if ((diff.x > 0 && axiosH > 0)
			|| (diff.x < 0 && axiosH < 0)
			|| (diff.y > 0 && axiosV > 0)
			|| (diff.y < 0 && axiosV < 0))
		{
			StelTransform transform = GetTransform();
			StelPointF position = transform.Position;
			position.x += axiosH * dt * speed * GetTransform().GetTrueRect().w + (OFFSET_SHIFT * axiosH);
			position.y += axiosV * dt * speed * GetTransform().GetTrueRect().h + (OFFSET_SHIFT * axiosV);

			StelRectF collider = {
				position.x - m_Collider.x,
				position.y - m_Collider.y,
				GetTransform().Size.x + m_Collider.x,
				GetTransform().Size.y + m_Collider.y
			};
			// Check colling with tile 
			if (m_CurrentLevel->IsColliding(collider.Resize(GetTransform().Scale)))
			{
				// Make the player be in before position
				StelPointF knockBack = transform.Position.Diff(position);
				knockBack.x += (10.0f * axiosH);
				knockBack.y += (10.0f * axiosV);
				other->SetTransform(other->GetTransform().Translate(knockBack));
			}
			else
			{
				// Confirm translade
				transform.Position = position;
				SetTransform(transform);
			}
		}
	}
}
