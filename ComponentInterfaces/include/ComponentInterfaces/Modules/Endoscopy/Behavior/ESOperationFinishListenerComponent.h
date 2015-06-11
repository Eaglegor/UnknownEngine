#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{

	namespace Endoscopy
	{
		class ESOperationResults;
	}

	namespace ComponentInterfaces
	{
		class ESOperationFinishListenerComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){ return "ESOperationFinishListenerComponent"; }

				virtual void onOperationFinished(const Endoscopy::ESOperationResults &results) = 0;
		};
	}
}
