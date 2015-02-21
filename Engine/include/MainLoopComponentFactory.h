#pragma once
#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
		class MainLoopComponentFactory : public BaseComponentFactory
		{
		public:
			MainLoopComponentFactory();
			
			virtual const char* getName() const;
			
			virtual IComponent* createMainLoopComponent( const ComponentDesc& desc );
		};
	}
}