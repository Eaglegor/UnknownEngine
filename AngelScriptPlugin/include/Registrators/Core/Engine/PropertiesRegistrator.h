#pragma once

#include <Properties/Properties.h>
#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IDataProvider;
	}

	namespace Behavior
	{
		class PropertiesRegistrator : public ClassValueTypeRegistrator<Core::Properties>
		{
			public:
				PropertiesRegistrator() :
					ClassValueTypeRegistrator< Core::Properties > ( "Properties", CORE_AS_NAMESPACE_NAME )
				{}

			protected:
				static const std::string& getString(Core::Properties* this_ptr, const std::string& name)
				{
					return this_ptr->get<std::string>(name);
				}
				
				static Core::IDataProvider* getDataProvider(Core::Properties* this_ptr, const std::string& name)
				{
					return this_ptr->get<Core::IDataProvider*>(name);
				}
				
				static Core::Properties& getNestedProperties(Core::Properties* this_ptr, const std::string& name)
				{
					return this_ptr->get_child(name);
				}
				
				static void setString(Core::Properties* this_ptr, const std::string& name, const std::string value)
				{
					this_ptr->set<std::string>(name, value);
				}
				
				static void setDataProvider(Core::Properties* this_ptr, const std::string& name, Core::IDataProvider* value)
				{
					this_ptr->set<Core::IDataProvider*>(name, value);
				}
				
				static void setNestedProperties(Core::Properties* this_ptr, const std::string& name, const Core::Properties& value)
				{
					this_ptr->set<Core::Properties>(name, value);
				}
				
				virtual bool registerMethods ( asIScriptEngine* script_engine ) const override
				{
					int result;
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "const std::string& getString(const std::string& in)", asFUNCTION(PropertiesRegistrator::getString), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::IDataProvider@ getDataProvider(const std::string& in)", asFUNCTION(PropertiesRegistrator::getDataProvider), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::Properties& getNestedProperties(const std::string& in)", asFUNCTION(PropertiesRegistrator::getNestedProperties), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setString(const std::string& in, const std::string& in)", asFUNCTION(PropertiesRegistrator::setString), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setDataProvider(const std::string& in, Core::IDataProvider@)", asFUNCTION(PropertiesRegistrator::setDataProvider), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
					
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "void setNestedProperties(const std::string& in, const Core::Properties& in)", asFUNCTION(PropertiesRegistrator::setNestedProperties), asCALL_CDECL_OBJFIRST);
					if(result < 0) return false;
				
					result = script_engine->RegisterObjectMethod(getRegisteredName(), "Core::Properties& opAssign(const Core::Properties& in)", asMETHODPR(Core::Properties, operator=, const Core::Properties&, Core::Properties&), asCALL_THISCALL);
					if(result < 0) return false;
					
					return true;
				}
		};
	}
}
