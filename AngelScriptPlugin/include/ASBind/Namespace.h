#pragma once

#include <angelscript.h>
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
				engine(subsystem->getScriptEngine())
				{
					prev_namespace = engine->GetDefaultNamespace();
					engine->SetDefaultNamespace((prev_namespace + ( prev_namespace.empty() ? "" : "::" ) + name).c_str());
				}

				~Namespace()
				{
					engine->SetDefaultNamespace(prev_namespace.c_str());
				}

		private:
				std::string prev_namespace;
				std::string name;
				asIScriptEngine* engine;

		};
	}
}