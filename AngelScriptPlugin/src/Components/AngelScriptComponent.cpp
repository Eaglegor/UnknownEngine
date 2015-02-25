#include <Components/AngelScriptComponent.h>
#include <MessageSystem/IMessageListener.h>
#include <Logging.h>
#include <ASIncludes.h>
#include <scriptbuilder/scriptbuilder.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		
		const Core::ComponentType AngelScriptComponent::TYPE = "Behavior.AngelScript";
		
		AngelScriptComponent::AngelScriptComponent ( const char* name, const AngelScriptComponentDesc& desc, Core::EngineContext* engine_context, AngelScriptSubsystem* angel_script_subsystem ):
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
		
		void AngelScriptComponent::init ()
		{
			asIScriptEngine* script_engine = angel_script_subsystem->getScriptEngine();
			
			CScriptBuilder script_builder;
			script_builder.StartNewModule(script_engine, getName());
			script_builder.AddSectionFromFile(desc.script_filename.c_str());
			
			script_builder.BuildModule();
			module = script_builder.GetModule();
			context = script_engine->CreateContext();
			
			asIScriptFunction *init_func = module->GetFunctionByDecl("void init(const std::string &in)");
			if(init_func)
			{
				context->Prepare(init_func);
				std::string obj_name = std::string(getName());
				context->SetArgObject(0, &obj_name);
				context->Execute();
			}
		}

		void AngelScriptComponent::shutdown()
		{
			asIScriptEngine* script_engine = angel_script_subsystem->getScriptEngine();
			asIScriptFunction *shutdown_func = module->GetFunctionByDecl("void shutdown()");
			if(shutdown_func)
			{
				context->Prepare(shutdown_func);
				context->Execute();
			}
			context->Release();
		}
		
	}
}