#pragma once

#include <ASBind/detail/Class.h>

#include <angelscript.h>
#include <ASBind/detail/Registrators/ConstructorRegistrator.h>



namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class ValueClass : public Class<T, ValueClass<T>>
		{
			typedef Class<T, ValueClass<T>> Base;
			
			public:
				ValueClass ( const std::string &name, Behavior::AngelScriptSubsystem *subsystem ) :
				Class<T, ValueClass<T>>(name, subsystem, subsystem->getScriptEngine())
				{
					if ( !subsystem->typeInfoIsBound<T>() )
					{
						subsystem->bindTypeInfo<T> ( name.c_str(), ClassType::VALUE_TYPE );
						Base::engine->RegisterObjectType ( Base::name.c_str(), sizeof ( T ), asOBJ_VALUE);
					}
					else
					{
						// LOG_ERROR - type already bound
					}
				}

				template<typename... Args>
				ValueClass& constructor()
				{
					ConstructorRegistrator<T>::template bindDefaultConstructor<Args...>(Base::subsystem);
					return *this;
				}

				ValueClass& destructor()
				{
					ConstructorRegistrator<T>::bindDefaultDestructor(Base::subsystem);
					return *this;
				}
		};
	}
}
