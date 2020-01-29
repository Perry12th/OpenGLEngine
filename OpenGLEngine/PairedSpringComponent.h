#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PairedSpringComponent
	{
		PairedSpringComponent(float _springConstant = 10.0f,
			float _restLength = 20.0f,
			ECSEntity _connectedEntityA = ECSEntity(),
			ECSEntity _connectedEntityB = ECSEntity())
			: springConstant(_springConstant),
			restLegnth(_restLength),
			connectedEntityA(_connectedEntityA),
			connectedEntityB(_connectedEntityB)
		{

		}
		float springConstant;
		float restLegnth;
		ECSEntity connectedEntityA;
		ECSEntity connectedEntityB;
	};
}

