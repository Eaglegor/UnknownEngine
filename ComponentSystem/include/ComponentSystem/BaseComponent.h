#pragma once

#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseComponent: public Core::IComponent
		{
			public:
				
				BaseComponent(const char* name):
				name(name),
				engine_specific_data(nullptr)
				{}
				
				virtual const char* getName() const override
				{
					return name.c_str();
				}

				virtual void setEngineSpecificData(EngineSpecificComponentData* data) override
				{
					this->engine_specific_data = data;
				}
				
				virtual EngineSpecificComponentData* getEngineSpecificData() override
				{
					return engine_specific_data;
				}
				
				virtual IComponentInterface* getInterface ( const ComponentType& type )
				{
					return nullptr;
				}
				
			private:
				std::string name;
				EngineSpecificComponentData* engine_specific_data;
		};
	}
}
