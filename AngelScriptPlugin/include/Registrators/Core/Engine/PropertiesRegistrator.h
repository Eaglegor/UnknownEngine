#pragma once

#include <Properties/Properties.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <Registrators/Core/Engine/PropertiesBehaviorWrapper.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class PropertiesRegistrator : public ClassValueTypeRegistrator<Core::Properties>
		{
			public:
				PropertiesRegistrator() :
					ClassValueTypeRegistrator< Core::Properties > ( "Properties", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				virtual bool registerMethods ( asIScriptEngine* script_engine ) const override
				{
					int result;
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "const std::string& getString(const std::string& in)", asFUNCTION(PropertiesBehaviorWrapper::getString), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Loader::IDataProvider@ getDataProvider(const std::string& in)", asFUNCTION(PropertiesBehaviorWrapper::getDataProvider), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::Properties& getNestedProperties(const std::string& in)", asFUNCTION(PropertiesBehaviorWrapper::getNestedProperties), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setString(const std::string& in, const std::string& in)", asFUNCTION(PropertiesBehaviorWrapper::setString), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setDataProvider(const std::string& in, Loader::IDataProvider@ in)", asFUNCTION(PropertiesBehaviorWrapper::setDataProvider), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setNestedProperties(const std::string& in, const Core::Properties& in)", asFUNCTION(PropertiesBehaviorWrapper::setNestedProperties), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					return true;
				}
		};
	}
}
