#pragma once

#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T, typename ActualObjectType>
		class FactoryRegistrator
		{
		public:
			
			template<typename... Args>
			static bool bind(ActualObjectType* (*f)(Args...), Behavior::AngelScriptSubsystem* subsystem)
			{
				return 0 <= subsystem->getScriptEngine()->RegisterObjectBehaviour(FormattedTypeName<T>()(subsystem).c_str(), asBEHAVE_FACTORY, format_factory_signature<T*, Args...>("f", subsystem).c_str(), asFUNCTION(f), asCALL_CDECL);	
			}
			
			template<typename... Args>
			static ActualObjectType* defaultFactory(Args&& ...args)
			{
				return new ActualObjectType(std::forward<Args>(args)...);
			}
			
			template<typename... Args>
			static bool bindDefault(Behavior::AngelScriptSubsystem* subsystem)
			{
				return bind(&FactoryRegistrator<T, ActualObjectType>::defaultFactory<Args...>, subsystem);
			}
		};
	}
}