#pragma once

#include <angelscript.h>
#include <ASBind/detail/FormatSignature.h>
#include <AngelScriptSubsystem.h>
#include <ASBind/detail/RefCountingWrapper.h>
#include <iostream>
#include <ASBind/Namespace.h>
#include <ASBind/detail/Registrators/MethodRegistrator.h>
#include <ASBind/detail/Registrators/Operators/Assignment/AssignOperatorRegistrator.h>
#include <ASBind/detail/Registrators/FactoryRegistrator.h>

namespace UnknownEngine
{
	namespace ASBind
	{
		template<typename T, typename DerivedClassType>
		class Class
		{
		public:
			template<typename Retval, typename... Args>
			DerivedClassType& method(Retval (T::*f)(Args...), const std::string &name)
			{
				MethodRegistrator<T>::bind_non_static(f, name.c_str(), subsystem);
				return getDerivedThis();
			}
			
			template<typename Retval, typename... Args>
			DerivedClassType& method(Retval (T::*f)(Args...), const std::string &name, const std::string &custom_signature)
			{
				MethodRegistrator<T>::bind_non_static(f, name.c_str(), subsystem, custom_signature.c_str());
				return getDerivedThis();
			}
			
			template<typename Retval, typename... Args>
			DerivedClassType& static_method(Retval (*f)(Args...), const std::string &name)
			{
				MethodRegistrator<T>::bind_static(f, name.c_str(), subsystem);
				return getDerivedThis();
			}
			
			template<typename Retval, typename... Args>
			DerivedClassType& static_method(Retval (*f)(Args...), const std::string &name, const std::string &custom_signature)
			{
				MethodRegistrator<T>::bind_static(f, name.c_str(), subsystem, custom_signature.c_str());
				return getDerivedThis();
			}
			
			DerivedClassType& operatorAssign()
			{
				AssignOperatorRegistrator<T>::bindDefault(subsystem);
				return getDerivedThis();
			}
			
			template<typename... Args>
			DerivedClassType& operatorAssign(T& (T::*f)(Args...))
			{
				AssignOperatorRegistrator<T>::bind(f);
				return getDerivedThis();
			}
			
			template<typename... Args>
			DerivedClassType& operatorAssign(T& (*f)(T*, Args...))
			{
				AssignOperatorRegistrator<T>::bind(f);
				return getDerivedThis();
			}
			
		protected:
			Class(const std::string& name, Behavior::AngelScriptSubsystem* subsystem, asIScriptEngine* engine):
			name(name),
			subsystem(subsystem),
			engine(engine)
			{}
			virtual ~Class(){};
			
			std::string name;
			Behavior::AngelScriptSubsystem* subsystem;
			asIScriptEngine* engine;
			
		private:
			DerivedClassType& getDerivedThis()
			{
				return static_cast<DerivedClassType&>(*this);
			}
		};
	}
}