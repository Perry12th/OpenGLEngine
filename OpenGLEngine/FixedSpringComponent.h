#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FixedSpringComponent
	{
		FixedSpringComponent(float _springConstant = 10.0f, 
			float _restLength = 20.0f,
			ECSEntity _connectedEntity = ECSEntity())
			: springConstant(_springConstant),
			restLegnth(_restLength),
			connectedEntity(_connectedEntity)
		{

		}
		float springConstant;
		float restLegnth;
		ECSEntity connectedEntity;
	};
}
