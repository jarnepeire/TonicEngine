#pragma once
#include "Transform.h"
#include "Subject.h"

namespace dae 
{
	class GameObject;
}

class Component
{
public:
	Component(dae::GameObject* parent);
	virtual ~Component() {}

	/* Initializes the component with the needed functionality */
	virtual void Initialize() = 0;

	/* Initializes the component with additional functionality, 
		at this point its parent GameObject will have all the components needed and initialized */
	virtual void PostInitialize() = 0;

	/* Updates the component every fixed timestep */
	virtual void FixedUpdate(float dt) = 0;

	/* Updates component with the elapsed time from previous frame */
	virtual void Update(float dt) = 0;

	/* Renders the components visuals if applicable */
	virtual void Render() = 0;

	/* Returns local position of component within the game object */
	const glm::vec3& GetLocalPosition() const { return m_Transform.GetPosition(); }

	/* Set local position of component within the game object */
	void SetLocalPosition(const float x, const float y);

	/* Get subject object of component, to be used to add observers to */
	std::unique_ptr<Subject>& GetSubject() { return m_pSubject; }

	/* Returns world position of component (local position within the game object + game object's position) */
	glm::vec3 GetWorldPosition() const;

	/* Returns a pointer to the parent game object */
	dae::GameObject* GetParentObject() { return m_pGameObject; }

protected:
	dae::GameObject* m_pGameObject = nullptr;
	dae::Transform m_Transform;
	std::unique_ptr<Subject> m_pSubject;
};

