#include <Components/AngelScriptComponent.h>
#include <MessageSystem/IMessageListener.h>
#include <LogHelper.h>
#include <ASIncludes.h>
#include <scriptbuilder/scriptbuilder.h>

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
		
		AngelScriptComponent::~AngelScriptComponent()
		{
		}
		
		Core::ComponentType AngelScriptComponent::getType() const
		{
			return TYPE;
		}
		
		void AngelScriptComponent::init ( const Core::Entity* parent_entity )
		{
			asIScriptEngine* script_engine = angel_script_subsystem->getScriptEngine();
			
			CScriptBuilder script_builder;
			script_builder.StartNewModule(script_engine, getName());
			script_builder.AddSectionFromFile(desc.script_filename.c_str());
			
			script_builder.BuildModule();
			module = script_builder.GetModule();
			context = script_engine->CreateContext();
			
			asIScriptFunction *install_func = module->GetFunctionByDecl("void install(const std::string &in)");
			if(install_func)
			{
				context->Prepare(install_func);
				std::string obj_name = std::string(getName());
				context->SetArgObject(0, &obj_name);
				context->Execute();
			}
		}

		void AngelScriptComponent::shutdown()
		{
			asIScriptEngine* script_engine = angel_script_subsystem->getScriptEngine();
			asIScriptFunction *uninstall_func = module->GetFunctionByDecl("void uninstall()");
			if(uninstall_func)
			{
				context->Prepare(uninstall_func);
				context->Execute();
			}
			context->Release();
			script_engine->DiscardModule(module->GetName());
		}
		
	}
}