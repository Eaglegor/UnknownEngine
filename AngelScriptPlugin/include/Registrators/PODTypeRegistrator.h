#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <string>
#include <type_traits>

namespace UnknownEngine
{
	namespace Behavior
	{
		template <typename T>
		class PODTypeRegistrator : public ITypeRegistrator
		{
		public:
			
			static_assert( std::is_pod<T>::value, "Only POD types can be registered using PODTypeRegistrator" );
			
			PODTypeRegistrator(const std::string& registered_name, const std::string &declaration_namespace = ""):
			registered_name(registered_name),
			declaration_namespace(declaration_namespace)
			{}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				script_engine->SetDefaultNamespace(declaration_namespace.c_str());
				int result = script_engine->RegisterObjectType(registered_name.c_str(), sizeof(T), asOBJ_VALUE | asOBJ_POD);
				script_engine->SetDefaultNamespace("");
				if(result < 0) return false;
				return registerRelatedTypes(script_engine);
			}
			
			virtual const char* getRegisteredName() const override
			{
				return registered_name.c_str();
			}
			
		protected:
			virtual bool registerRelatedTypes( asIScriptEngine* script_engine) const
			{
				return true;
			}
			
		private:
			const std::string registered_name;
			const std::string declaration_namespace;
		};
	}
}