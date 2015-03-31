#pragma once

#include <AngelScript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		class Namespace
		{
			public:
				Namespace(const std::string &name, Behavior::AngelScriptSubsystem *subsystem):
				name(name),
				subsystem(subsystem),
				engine(subsystem->getScriptEngine())
				{
					prev_namespace = engine->GetDefaultNamespace();
					engine->SetDefaultNamespace(prev_namespace + "::" + name);
				}

				~Namespace()
				{
					engine->SetDefaultNamespace(prev_namespace);
				}

		private:
				std::string prev_namespace;
				std::string name;
				Behavior::AngelScriptSubsystem* subsystem;
				asIScriptEngine* engine;

		};
	}
}
