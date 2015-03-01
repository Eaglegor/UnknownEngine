#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class IComponentInterface
		{
		public:
			virtual ~IComponentInterface(){}
			
			constexpr static const char* getTypeName()
			{
				return "UnknownComponentInterface";
			}
		};
	}
}