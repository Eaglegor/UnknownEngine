#include <Components/AngelScriptComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		const Core::ComponentType AngelScriptComponent::TYPE = "Behavior.AngelScript";
		
		AngelScriptComponent::AngelScriptComponent ( const std::string& name, const AngelScriptComponentDesc& desc, Core::EngineContext* engine_context, AngelScriptSubsystem* angel_script_subsystem ):
		BaseComponent(name),
		desc(desc),
		engine_context(engine_context),
		angel_script_subsystem(angel_script_subsystem)
		{
		}
		
		Core::ComponentType AngelScriptComponent::getType() const
		{
			return TYPE;
		}
		
		void AngelScriptComponent::init ( const Core::Entity* parent_entity )
		{
			
		}

		void AngelScriptComponent::shutdown()
		{
			
		}
		
		void AngelScriptComponent::addListener ( Core::IMessageListener* listener )
		{
			
		}

		void AngelScriptComponent::removeListener ( Core::IMessageListener* listener )
		{
			
		}
		
	}
}