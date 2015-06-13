#pragma once

#include <Descriptors/Schemas/IDescriptorFieldSetter.h>
#include <Descriptors/Schemas/DescriptorSetterFunction.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Utils
	{
		
		template<>
		class DescriptorFieldSetter<Core::IComponent*> : public IDescriptorFieldSetter
		{
		public:
			DescriptorFieldSetter(DescriptorSetterFunction<Core::IComponent*> &setter)
			{
				this->setter = setter;
			}
			
			void setValue(const PropertiesTreeNode& value)
			{
				Core::IComponent* component = Core::ComponentsManager::getSingleton()->findComponent(value.getValue());
				setter(component);
			}
			
		private:
			DescriptorSetterFunction<Core::IComponent*> setter;
		};
	}
}