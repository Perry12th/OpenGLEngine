#include "PairedSpringSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	PairedSpringSystem::PairedSpringSystem()
	{
		requireComponent<PairedSpringComponent>();
	}

	void PairedSpringSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& spring = e.getComponent<PairedSpringComponent>();

			if (spring.connectedEntityA.hasComponent<TransformComponent>()
				&& spring.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = spring.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = spring.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - spring.restLegnth;
					Vector3 force = -glm::normalize(relativePosition);
					force *= spring.springConstant * deltaL;
					
					if (spring.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
					{
						spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}

					if (spring.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
					{
						spring.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}


					getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position,
						deltaL > 0 ? Color::Red : Color::Green);
				}
			}
		}
	}
}
