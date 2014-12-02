#pragma once

#include <Registrators/ITypeRegistrator.h>
#include <string>

namespace UnknownEngine
{
	namespace Behavior
	{
		template<typename T>
		class ClassReferenceTypeRegistrator : public ITypeRegistrator
		{
		public:
			ClassReferenceTypeRegistrator(const std::string& registered_name, const std::string& declaration_namespace = ""):
			registered_name(registered_name),
			declaration_namespace(declaration_namespace),
			full_name(declaration_namespace.empty() ? registered_name : declaration_namespace + "::" + registered_name)
			{}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				script_engine->SetDefaultNamespace(declaration_namespace.c_str());
				
				bool success = registerTypeImpl(script_engine);
				
				script_engine->SetDefaultNamespace("");
				
				return success;
			}

			virtual const char* getRegisteredName() const override
			{
				return registered_name.c_str();
			}
			
			virtual const char* getRegisteredNameWithNamespace() const override
			{
				return full_name.c_str();
			}
			
		protected:
			virtual bool registerProperties( asIScriptEngine* script_engine ) const
			{
				return true;
			}
			
			virtual bool registerMethods( asIScriptEngine* script_engine ) const
			{
				return true;
			}

			virtual bool registerRelatedTypes( asIScriptEngine* script_engine) const
			{
				return true;
			}

		private:
			bool registerTypeImpl(asIScriptEngine* script_engine) const
			{
				int result = script_engine->RegisterObjectType(registered_name.c_str(), 0, asOBJ_REF | asOBJ_NOCOUNT);
				if(result < 0) return false;
				return registerProperties( script_engine ) && registerMethods( script_engine ) && registerRelatedTypes(script_engine);
			}
			
			const std::string registered_name;
			const std::string declaration_namespace;
			const std::string full_name;
		};
	}
}