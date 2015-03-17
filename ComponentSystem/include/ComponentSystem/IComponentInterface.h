#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class IComponentInterface
		{
		public:
			virtual ~IComponentInterface(){}
			
			constexpr static const char* getType()
			{
				return "UnknownComponentInterface";
			}
		};
	}
}