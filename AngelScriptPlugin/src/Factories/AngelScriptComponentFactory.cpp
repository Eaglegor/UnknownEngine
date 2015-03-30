#include <Factories/AngelScriptComponentFactory.h>
#include <Components/AngelScriptComponent.h>
#include <Parsers/AngelScriptComponentDescriptorGetter.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		static AngelScriptComponentDescriptorGetter angel_script_descriptor_getter;
		
		AngelScriptComponentFactory::AngelScriptComponentFactory ( AngelScriptSubsystem* angel_script_subsystem):
		angel_script_subsystem(angel_script_subsystem)
		{
			CreatableObjectDesc desc;
			desc.type = AngelScriptComponent::TYPE;
			desc.creator = std::bind(&AngelScriptComponentFactory::createAngelScriptComponent, this, std::placeholders::_1);
			registerCreator(desc);
		}

		const char* AngelScriptComponentFactory::getName() const
		{
			return "Behavior.AngelScriptComponentFactory";
		}
		
		Core::IComponent* AngelScriptComponentFactory::createAngelScriptComponent ( const Core::ComponentDesc& desc )
		{
			AngelScriptComponent* component = nullptr;
			try
			{
				AngelScriptComponentDesc actual_desc = desc.descriptor.apply_visitor(angel_script_descriptor_getter);
				component = new AngelScriptComponent(desc.name.c_str(), actual_desc, angel_script_subsystem);
			}
			catch(const AngelScriptComponentDescriptorGetter::NoDescriptorProvided &e)
			{
				return nullptr;
			}
			return component;
		}
		
	}
}