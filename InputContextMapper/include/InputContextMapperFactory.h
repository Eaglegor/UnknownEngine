#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace IO
	{

		class InputContextMapper;
		class InputContextMapperFactory : public Core::BaseComponentFactory
		{
		public:
			InputContextMapperFactory();
			virtual const char* getName() const {return "InputContextMapper.Factory";}
			
		private:
			InputContextMapper* mapper;
			
			Core::IComponent* createInputContextMapper(const Core::ComponentDesc& desc);
			void destroyInputContextMapper(Core::IComponent* component);
		};
	}
}