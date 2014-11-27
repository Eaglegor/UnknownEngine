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
			
			static_assert( std::is_pod<T>, "Only POD types can be registered using PODTypeRegistrator" );
			
			PODTypeRegistrator(const std::string& registered_name):
			registered_name(registered_name)
			{}
			
			virtual bool registerType ( asIScriptEngine* script_engine ) const override
			{
				int result = script_engine->RegisterObjectType(registered_name.c_str(), sizeof(T), asOBJ_VALUE | asOBJ_POD);
				return result >= 0;
			}
			
		private:
			const std::string registered_name;
		};
	}
}