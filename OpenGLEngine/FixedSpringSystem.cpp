#include "FixedSpringSystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	FixedSpringSystem::FixedSpringSystem()
	{
		requireComponent<FixedSpringComponent>();
		requireComponent<TransformComponent>();
	}

	void FixedSpringSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& spring = e.getComponent<FixedSpringComponent>();
			auto& springPosition = e.getComponent<TransformComponent>().position;

			if (spring.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& spring.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forcAcc = spring.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& position = spring.connectedEntity.getComponent<TransformComponent>().position;

				Vector3 relativePosition = position - springPosition;
				float currentLength = glm::length(relativePosition);
				if (currentLength > 0)
				{
					float deltaL = currentLength - spring.restLegnth;
					Vector3 force = -glm::normalize(relativePosition);
					force *= spring.springConstant * deltaL;
					forcAcc.AddForce(force);

					getWorld().data.renderUtil->DrawLine(springPosition, position,
						deltaL > 0 ? Color::Red : Color::Green);
				}
			}
		}
	}
}
