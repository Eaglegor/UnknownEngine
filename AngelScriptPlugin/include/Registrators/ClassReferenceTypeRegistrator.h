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
			declaration_namespace(declaration_namespace)
			{}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				script_engine->SetDefaultNamespace(declaration_namespace.c_str());
				
				bool success = registerTypeImpl(script_engine);
				
				script_engine->SetDefaultNamespace("");
				
				return success;
			}

			virtual const char* getRegisteredName() const
			{
				return registered_name.c_str();
			}
			
		protected:
			typedef T class_type;

			virtual bool registerProperties( asIScriptEngine* script_engine ) const
			{
				return true;
			}
			
			virtual bool registerMethods( asIScriptEngine* script_engine ) const
			{
				return true;
			}


		private:
			bool registerTypeImpl(asIScriptEngine* script_engine) const
			{
				int result = script_engine->RegisterObjectType(registered_name.c_str(), 0, asOBJ_REF | asOBJ_NOCOUNT);
				if(result < 0) return false;
				return registerProperties( script_engine ) && registerMethods( script_engine );
			}
			
			const std::string registered_name;
			const std::string declaration_namespace;
		};
	}
}