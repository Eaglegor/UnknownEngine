#pragma once

#include <angelscript.h>
#include <ASBind/detail/FormatSignature.h>
#include <ASBind/detail/Registrators/MethodRegistrator.h>
#include <ASBind/Namespace.h>
#include <AngelScriptSubsystem.h>
#include <new>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T>
		class ValueClass
		{
			public:
				ValueClass ( const std::string &name, Behavior::AngelScriptSubsystem *subsystem ) :
					name ( name ),
					subsystem ( subsystem ),
					engine ( subsystem->getScriptEngine() )
				{
					if ( !subsystem->typeNameIsBound<T>() )
					{
						subsystem->bindTypeInfo<T> ( name.c_str(), ClassType::VALUE_TYPE );
						engine->RegisterObjectType ( name.c_str(), sizeof ( T ), asOBJ_VALUE );
					}
					else
					{
						// LOG_ERROR - type already bound
					}
				}

				template<typename Retval, typename... Args>
				ValueClass& method ( Retval ( T::*f ) ( Args... ), const std::string &name )
				{
					MethodRegistrator<T>::bind_non_static(f, name.c_str(), subsystem);
					return *this;
				}

				template<typename Retval, typename... Args>
				ValueClass& static_method ( Retval ( T::*f ) ( Args... ), const std::string &name )
				{
					MethodRegistrator<T>::bind_static(f, name.c_str(), subsystem);
				}

				template<typename... Args>
				ValueClass& constructor()
				{
					engine->RegisterObjectBehaviour ( name, asBEHAVE_CONSTRUCT, "void f(" + FormattedArgumentsString<Args...>() () + ")", asFUNCTION ( ValueClass::constr ), asCALL_CDECL_OBJLAST );
				}

				ValueClass& default_constructor()
				{
					engine->RegisterObjectBehaviour ( name, asBEHAVE_CONSTRUCT, "void f(" + FormattedArgumentsString<Args...>() () + ")", asFUNCTION ( ValueClass::def_constr ), asCALL_CDECL_OBJLAST );
				}

				ValueClass& destructor()
				{
					engine->RegisterObjectBehaviour ( name, asBEHAVE_DESTRUCT, "void f()", asFUNCTION ( ValueClass::destr ), asCALL_CDECL_OBJLAST );
				}

			private:
				template<typename... Args>
				static void constr ( void* memory, Args && ...args )
				{
					new ( memory ) T ( std::forward<Args> ( args )... );
				}

				static void def_constr ( void* memory )
				{
					new ( memory ) T ();
				}

				static void destr ( void* memory )
				{
					static_cast<T*> ( memory )->~T();
				}

				std::string name;
				Behavior::AngelScriptSubsystem* subsystem;
				asIScriptEngine* engine;

		};
	}
}
