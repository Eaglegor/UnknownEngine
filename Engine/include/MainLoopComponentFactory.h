#pragma once
#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{
        class Engine;

		class EngineCoreComponentsFactory : public BaseComponentFactory
		{
		public:
			EngineCoreComponentsFactory(Engine &engine);
			
			virtual const char* getName() const;
			
			virtual IComponent* createMainLoopComponent( const ComponentDesc& desc );
            virtual IComponent* createEngineStarterComponent( const ComponentDesc& desc );

        private:
            Engine &engine;
		};
	}
}