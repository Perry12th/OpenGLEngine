#include "BuoyancySystem.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& force = e.getComponent<ForceAccumulatorComponent>();
			auto position = e.getComponent<TransformComponent>().position;
			auto buoy = e.getComponent<BuoyancyComponent>();

			float d = ((buoy.maxDepth / 2) - (position.y - liquidVolume.y)) / buoy.maxDepth;

			Color color = Color::Red;
			if (d <= 0) 
			{
				color = Color::Orange;
				//Force = 0 
			} 
			else if (d >= 1) 
			{ 
				color = Color::Blue;
				float vp = liquidDensity * buoy.volume;
				force.AddForce(Vector3(0, vp, 0));
			} 
			else // 0 < d < 1
			{ 
				color = Color::Green;
				float dvp = d * liquidDensity * buoy.volume;
				force.AddForce(Vector3(0, dvp, 0));
			}

			getWorld().data.renderUtil->DrawSphere(position, buoy.maxDepth, color);
			getWorld().data.renderUtil->DrawLine(liquidVolume, position, color);
		}
	}
}
