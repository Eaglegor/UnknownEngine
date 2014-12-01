#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <Registrators/Basic/ASNamespaceName.h>
#include <scriptstdstring/scriptstdstring.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class StdStringRegistrator : public ITypeRegistrator
		{
		public:
			StdStringRegistrator():
			registered_type_name("string"),
			declaration_namespace(BASIC_AS_NAMESPACE_NAME),
			full_name(BASIC_AS_NAMESPACE_NAME+"::"+registered_type_name)
			{}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				script_engine->SetDefaultNamespace(declaration_namespace.c_str());
				
				RegisterStdString(script_engine);
				
				script_engine->SetDefaultNamespace("");
				return true;
			}
			
			virtual const char* getRegisteredName() const
			{
				return registered_type_name.c_str();
			}
			
			virtual const char* getRegisteredNameWithNamespace() const
			{
				return full_name.c_str();
			}
			
		private:
			std::string registered_type_name;
			std::string declaration_namespace;
			std::string full_name;
		};
	}
}